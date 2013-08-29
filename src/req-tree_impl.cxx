/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "req-tree_impl.h"

ReqTreeImpl::ReqTreeImpl (HLogPtr logger,
                          std::shared_ptr<RequirementFactory> req_factory)
  : m_logger (logger),
    m_req_factory (req_factory)
{
  m_last_id = 0;
  std::stringstream ss;
  ss << boost::uuids::random_generator ()();
  m_uuid = ss.str ();
  m_dirty = false;
  m_root = m_req_factory->create ("root", "root", "root");
}

std::string
ReqTreeImpl::add_new_child (std::shared_ptr<Requirement> parent,
                            std::shared_ptr<Requirement> child)
{
  /* Here we assume that the child will not have children */
  child->set_id (next_id ());
  return add_child (parent, child);
}

std::string
ReqTreeImpl::add_new_sibling (std::shared_ptr<Requirement> sibling,
                              std::shared_ptr<Requirement> new_sibling)
{
  auto parent = sibling->parent ();
  /* Here we assume that the new_sibling will not have children */
  new_sibling->set_id (next_id ());
  add_to_req_id_map (new_sibling);

  auto children = parent->children ();
  auto pos = std::find (children->begin (), children->end (), sibling);
  ASSERT ((pos != children->end ()), "sibling=%s not a child of %s",
          sibling->id ().c_str (), parent->id ().c_str ());
  pos ++;
  new_sibling->set_parent (parent);
  children->insert (pos, new_sibling);
  set_dirty ();
  return new_sibling->id ();
}

std::string
ReqTreeImpl::add_child (std::shared_ptr<Requirement> parent,
                        std::shared_ptr<Requirement> child)
{
  add_to_req_id_map (child);

  std::shared_ptr<Requirement> real_parent (parent);
  if (!real_parent)
    {
      real_parent = m_root;
    }

  auto children = real_parent->children ();
  child->set_parent (real_parent);
  children->push_back (child);
  set_dirty ();
  return child->id ();
}

std::shared_ptr<Requirement>
ReqTreeImpl::add_duplicate_child (std::shared_ptr<Requirement> parent,
                                  std::shared_ptr<Requirement> child)
{
  /* Here we assume that the child can have children */
  auto duplicate_child = duplicate_tree (child);
  add_to_req_id_map (duplicate_child);

  auto children = parent->children ();
  duplicate_child->set_parent (parent);
  children->push_back (duplicate_child);
  set_dirty ();
  return duplicate_child;
}


void
ReqTreeImpl::detach (std::shared_ptr<Requirement> node)
{
  auto parent = node->parent ();
  auto children = parent->children ();
  auto pos = std::find (children->begin (), children->end (), node);
  ASSERT ((pos != children->end ()), "node=%s is not a child of %s",
          node->id ().c_str (), parent->id ().c_str ());
  children->erase (pos);
  remove_from_req_id_map (node);
}

bool
ReqTreeImpl::is_first_child (std::shared_ptr<const Requirement> req) const
{
  auto parent = req->parent ();
  auto children = parent->children ();
  return (children->front () == req);
}

bool
ReqTreeImpl::is_last_child (std::shared_ptr<const Requirement> req) const
{
  auto parent = req->parent ();
  auto children = parent->children ();
  return (children->back () == req);
}

bool
ReqTreeImpl::is_top_level (std::shared_ptr<const Requirement> req) const
{
  auto parent = req->parent ();
  return (parent->id () == "root");
}

void
ReqTreeImpl::up_child (std::shared_ptr<Requirement> node)
{
  auto parent = node->parent ();
  auto children = parent->children ();
  auto pos = std::find (children->begin (), children->end (), node);
  ASSERT ((pos != children->end ()), "node=%s is not a child of %s",
          node->id ().c_str (), parent->id ().c_str ());
  ASSERT ((pos != children->begin ()),
          "cannot up-child. node=%s is first child", node->id ().c_str ());

  *(pos) = *(pos - 1);
  *(pos - 1) = node;
  set_dirty ();
}

void
ReqTreeImpl::down_child (std::shared_ptr<Requirement> node)
{
  auto parent = node->parent ();
  auto children = parent->children ();
  auto pos = std::find (children->begin (), children->end (), node);
  ASSERT ((pos != children->end ()), "node=%s is not a child of %s",
          node->id ().c_str (), parent->id ().c_str ());
  ASSERT ((*pos != children->back ()),
          "cannot down-child. node=%s is last child", node->id ().c_str ());

  *(pos) = *(pos + 1);
  *(pos + 1) = node;
  set_dirty ();
}

void
ReqTreeImpl::up_level (std::shared_ptr<Requirement> node)
{
  auto parent = node->parent ();
  auto grand_parent = parent->parent ();
  auto parent_children = parent->children ();
  auto grand_parent_children = grand_parent->children ();

  auto node_pos = std::find
    (parent_children->begin (), parent_children->end (), node);
  ASSERT ((node_pos != parent_children->end ()), "node=%s is not a child of %s",
          node->id ().c_str (), parent->id ().c_str ());

  auto parent_pos = std::find
    (grand_parent_children->begin (), grand_parent_children->end (), parent);
  ASSERT ((parent_pos != grand_parent_children->end ()),
          "node=%s is not a child of %s",
          node->id ().c_str (), parent->id ().c_str ());

  parent_children->erase (node_pos);
  parent_pos ++;
  node->set_parent (grand_parent);
  grand_parent_children->insert (parent_pos, node);
  set_dirty ();
}

void
ReqTreeImpl::down_level (std::shared_ptr<Requirement> node)
{
  auto parent = node->parent ();
  auto parent_children = parent->children ();

  auto node_pos = std::find
    (parent_children->begin (), parent_children->end (), node);
  ASSERT ((node_pos != parent_children->end ()), "node=%s is not a child of %s",
          node->id ().c_str (), parent->id ().c_str ());
  ASSERT ((node_pos != parent_children->begin ()),
          "node=%s is the first child. cannot down-level",
          node->id ().c_str ());

  auto sibling = *(node_pos - 1);
  auto sibling_children = sibling->children ();

  parent_children->erase (node_pos);
  node->set_parent (sibling);
  sibling_children->push_back (node);
  set_dirty ();
}

size_t
ReqTreeImpl::height (void) const
{
  return (compute_height (m_root) - 1);
}

std::shared_ptr<Requirement>
ReqTreeImpl::get (const std::string & reqid) const
{
  return m_req_id_map.at (reqid);
}

size_t
ReqTreeImpl::compute_height (std::shared_ptr<const Requirement> node) const
{
  size_t max_child_height = 0;
  auto end = node->children_cend ();
  for (auto it = node->children_cbegin (); it != end; ++it)
    {
      auto child = *it;
      size_t child_height = compute_height (child);
      if (child_height > max_child_height)
        {
          max_child_height = child_height;
        }
    }
  return (max_child_height + 1);
}

std::string
ReqTreeImpl::next_id (void)
{
  std::ostringstream os;
  m_last_id += 1;
  os << "r" << m_last_id;
  return os.str ();
}

std::shared_ptr<Requirement>
ReqTreeImpl::duplicate_tree (std::shared_ptr<const Requirement> node)
{
  auto new_node = m_req_factory->create
    (next_id (), node->title (), node->description ());
  auto children = new_node->children ();
  auto end = node->children_cend ();
  for (auto it = node->children_cbegin (); it != end; ++it)
    {
      auto child = *it;
      auto new_child = duplicate_tree (child);
      new_child->set_parent (new_node);
      children->push_back (new_child);
    }
  return new_node;
}

void
ReqTreeImpl::add_to_req_id_map (std::shared_ptr<Requirement> req)
{
  /* The req should have a valid reqid */
  ASSERT ((!req->id ().empty ()), "Requirement::id is empty");

  m_req_id_map[req->id ()] = req;
  auto end = req->children_cend ();
  for (auto it = req->children_cbegin (); it != end; ++it)
    {
      auto child = *it;
      add_to_req_id_map (child);
    }
}

void
ReqTreeImpl::remove_from_req_id_map (std::shared_ptr<Requirement> req)
{
  m_req_id_map.erase (req->id ());
  auto end = req->children_cend ();
  for (auto it = req->children_cbegin (); it != end; ++it)
    {
      auto child = *it;
      remove_from_req_id_map (child);
    }
}

void
ReqTreeImpl::load (const std::string & data)
{
  /* Clear/overwrite the old values */
  m_root = m_req_factory->create ("root", "root", "root");
  m_req_id_map.clear ();
  m_dirty = false;

  boost::property_tree::ptree pt;
  std::stringstream ss (data);
  boost::property_tree::read_json (ss, pt);
  m_last_id = pt.get<int> ("last-id");
  m_uuid = pt.get<std::string> ("uuid");
  auto req_array = pt.get_child ("requirements");
  auto root_ptree = get_req_ptree (req_array, "root");
  load_children (m_root, root_ptree, req_array);
}

void
ReqTreeImpl::load (std::ifstream & file)
{
  std::string data, line;
  while (std::getline (file, line))
    {
      data += line;
    }
  load (data);
}

boost::property_tree::ptree
ReqTreeImpl::get_req_ptree (boost::property_tree::ptree & req_ptree_array,
                            const std::string & reqid)
{
  auto end = req_ptree_array.end ();
  for (auto it = req_ptree_array.begin (); it != end; ++it)
    {
      /* req_ptree_array is an array containing of std::pair so, in
       * order to access the req ptree element we get the second item
       * of the pair */
      auto req = it->second;
      if (req.get<std::string> ("reqid") == reqid)
        {
          return req;
        }
    }
  ASSERT ((false), "Requirement=%s not found", reqid.c_str ());
}

void
ReqTreeImpl::load_children (std::shared_ptr<Requirement> parent,
                            boost::property_tree::ptree & parent_data,
                            boost::property_tree::ptree & req_ptree_array)
{
  auto child_array = parent_data.get_child ("children");

  auto end = child_array.end ();
  for (auto it = child_array.begin (); it != end; ++it)
    {
      /* access the second element (which is a ptree) from std::pair
         and get its value referenced by an empty string */
      auto reqid = it->second.get <std::string> ("");
      auto child_data = get_req_ptree (req_ptree_array, reqid);
      auto child = m_req_factory->create (
        child_data.get <std::string> ("reqid"),
        child_data.get <std::string> ("title"),
        child_data.get <std::string> ("description"));
      auto children = parent->children ();
      children->push_back (child);
      child->set_parent (parent);
      add_to_req_id_map (child);
      load_children (child, child_data, req_ptree_array);
    }
}

std::string
ReqTreeImpl::serialize (void)
{
  boost::property_tree::ptree pt;
  pt.put ("last-id", m_last_id);
  pt.put ("uuid", m_uuid);
  boost::property_tree::ptree req_array;
  serialize_tree (m_root, &req_array);
  pt.put_child ("requirements", req_array);
  std::stringstream ss;
  boost::property_tree::write_json (ss, pt);
  return ss.str();
}

void
ReqTreeImpl::serialize_tree (std::shared_ptr<Requirement> node,
                             boost::property_tree::ptree * req_array)
{
  req_array->push_back (std::make_pair ("", node->dump ()));
  auto end = node->children_cend ();
  for (auto it = node->children_cbegin (); it != end; ++it)
    {
      serialize_tree (*it, req_array);
    }
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
