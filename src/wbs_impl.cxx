/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "_namespace.h"
#include "wbs_impl.h"

NAMESPACE__THITTAM__START

WBSImpl::WBSImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

bool
WBSImpl::is_first_child (const Path & path) const
{
  // todo
  return false;
}

bool
WBSImpl::is_last_child (const Path & path) const
{
  // todo
  return false;
}

bool
WBSImpl::is_top_level (const Path & path) const
{
  // todo
  return false;
}

void
WBSImpl::add_child (const Path & parent_path)
{
  /* Find the parent */
  Task * parent = &m_root;
  for (auto index : parent_path.parts ())
  {
    parent = parent->child (index);
  }

  /* Add to tree */
  auto task = std::make_unique<Task> ();
  auto child_path = parent->add_child (task.get ());

  /* Add to flat-wbs */
  m_flat_wbs.push_back (Entry (child_path, std::move (task)));

  notify_observers_node_inserted (child_path);
}

void
WBSImpl::add_sibling (const Path & sibling_path)
{
  ASSERT ((sibling_path.parts_length () != 0), "Sibling path cannot be empty");

  /* Find the sibling */
  Task * sibling = &m_root;
  size_t sibling_index = 0;
  for (auto index : sibling_path.parts ())
  {
    sibling = sibling->child (index);
    sibling_index = index;
  }
  auto parent = sibling->parent ();

  auto task = std::make_unique<Task> ();
  parent->add_child_after (
    sibling_index, task.get (),
    std::bind (
      &WBSImpl::notify_observers_node_inserted, this, std::placeholders::_1),
    std::bind (
      &WBSImpl::notify_observers_node_changed, this, std::placeholders::_1));
}

void
WBSImpl::notify_observers_node_inserted (const WBS::Path & path)
{
  for (auto observer : m_observers)
  {
    observer->wbs_observer_node_inserted (path);
  }
}

void
WBSImpl::notify_observers_node_changed (const WBS::Path & path)
{
  for (auto observer : m_observers)
  {
    observer->wbs_observer_node_changed (path);
  }
}

void
WBSImpl::notify_observers_node_deleted (const WBS::Path & path)
{
  for (auto observer : m_observers)
  {
    observer->wbs_observer_node_deleted (path);
  }
}

void
WBSImpl::notify_observers_node_reordered (
  const WBS::Path & path, const std::vector<int> & new_order)
{
  for (auto observer : m_observers)
  {
    observer->wbs_observer_node_reordered (path, new_order);
  }
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
