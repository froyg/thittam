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
  parent->add_child (std::move (task));
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
  parent->add_child_after (sibling_index, std::move (task));
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
