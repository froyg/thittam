/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__a0055c6a_00db_11e3_ae98_68a3c42125fd
#define HIPRO_THITTAM__a0055c6a_00db_11e3_ae98_68a3c42125fd

#include <memory>
#include <string>

#include <boost/signals2.hpp>
#include <boost/property_tree/ptree.hpp>

#include "common.h"
#include "req-tree.h"
#include "log.h"

class ReqTreeImpl : public ReqTree
{
public:
  /*--- ctor/dtor ---*/
  ReqTreeImpl (hipro::log::Logger* logger, std::shared_ptr<RequirementFactory> req_factory);
  ~ReqTreeImpl () {}

  /*--- methods required by the ReqTree interface ---*/
  signal_tree_dirty_t & signal_tree_dirty (void)
  {
    return m_signal_tree_dirty;
  }

  std::string add_new_child (std::shared_ptr<Requirement> parent,
                             std::shared_ptr<Requirement> new_req);
  std::string add_new_sibling (std::shared_ptr<Requirement> sibling,
                               std::shared_ptr<Requirement> new_req);
  std::string add_child (std::shared_ptr<Requirement> parent,
                         std::shared_ptr<Requirement> req);
  std::shared_ptr<Requirement> add_duplicate_child (
    std::shared_ptr<Requirement> parent, std::shared_ptr<Requirement> child);

  void detach (std::shared_ptr<Requirement> node);

  bool is_first_child (std::shared_ptr<const Requirement> req) const;
  bool is_last_child (std::shared_ptr<const Requirement> req) const;
  bool is_top_level (std::shared_ptr<const Requirement> req) const;

  void up_child (std::shared_ptr<Requirement> req);
  void down_child (std::shared_ptr<Requirement> req);
  void up_level (std::shared_ptr<Requirement> req);
  void down_level (std::shared_ptr<Requirement> req);

  void recompute_work (std::shared_ptr<Requirement> req);

  size_t height (void) const;
  std::shared_ptr<Requirement> get (const std::string & reqid) const;
  std::shared_ptr<Requirement> root (void) const
  {
    return m_root;
  }

  bool is_dirty (void) const
  {
    return m_dirty;
  }
  void clear_dirty (void)
  {
    m_dirty = false;
  }
  void set_dirty (void)
  {
    m_dirty = true;
    m_signal_tree_dirty ();
  }

  void load (const std::string & data);
  void load (std::ifstream & file);
  std::string serialize (void);

private:
  size_t compute_height (std::shared_ptr<const Requirement> node) const;
  std::string next_id (void);
  std::shared_ptr<Requirement> duplicate_tree (
    std::shared_ptr<const Requirement> node);
  void add_to_req_id_map (std::shared_ptr<Requirement> req);
  void remove_from_req_id_map (std::shared_ptr<Requirement> req);
  void serialize_tree (std::shared_ptr<Requirement> node,
                       boost::property_tree::ptree * req_ptree);
  boost::property_tree::ptree get_req_ptree (
    boost::property_tree::ptree & req_ptree_array, const std::string & reqid);
  void load_children (
    std::shared_ptr<Requirement> parent,
    boost::property_tree::ptree  & parent_data,
    boost::property_tree::ptree & req_ptree_array);
  int recalculate_and_set_work (std::shared_ptr<Requirement> req);
  std::string compute_work_string (int work);

private:
  hipro::log::Logger* logger;
  std::shared_ptr<RequirementFactory> m_req_factory;

  signal_tree_dirty_t m_signal_tree_dirty;
  int m_last_id;
  std::string m_uuid;
  bool m_dirty;
  std::shared_ptr<Requirement> m_root;

  typedef std::map< const std::string, std::shared_ptr<Requirement> > req_id_map_t;
  req_id_map_t m_req_id_map;
};

class ReqTreeFactoryImpl : public ReqTreeFactory
{
public:
  ReqTreeFactoryImpl (hipro::log::Logger* logger,
                      std::shared_ptr<RequirementFactory> req_factory)
    : logger (logger),
      m_req_factory (req_factory)
  {
  }

  std::shared_ptr<ReqTree> create (void)
  {
    return std::make_shared<ReqTreeImpl> (logger, m_req_factory);
  }

private:
  hipro::log::Logger* logger;
  std::shared_ptr<RequirementFactory> m_req_factory;
};

#endif // HIPRO_THITTAM__a0055c6a_00db_11e3_ae98_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
