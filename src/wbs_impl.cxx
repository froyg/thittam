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
  return path.last_part () == 0;
}


bool
WBSImpl::is_last_child (const Path & path) const
{
  auto parent = &m_root;
  for (size_t i = 0; i < (path.parts_length() - 1); ++i)
  {
    parent = parent->child (path[i]);
  }

  if (path.last_part () == (parent->children_count () - 1))
  {
    return true;
  }

  return false;
}


bool
WBSImpl::is_top_level (const Path & path) const
{
  return path.parts_length () == 1;
}


Task *
WBSImpl::get_task_at_level(const Path & path, size_t level)
{
  Task * parent = &m_root;
  for (size_t i = 0; i < path.parts_length() and i < level; i++)
  {
    parent = parent->child (path[i]);
  }
  return parent;
}

Task*
WBSImpl::get_task (const Path& path)
{
  Task* task = &m_root;
  for (auto i : path.parts ())
  {
    task = task->child (i);
  }
  return task;
}

void
WBSImpl::add_child (const Path & path)
{
  /* Find the parent */
  auto parent = get_task_at_level (path, path.parts_length ());

  /* Make a new node/task */
  auto task = std::make_unique<Task> ();

  /* Add to tree */
  parent->add_child (std::move (task));
}

void
WBSImpl::add_sibling (const Path & path)
{
  ASSERT ((path.parts_length () != 0), "Sibling path cannot be empty");

  auto parent = get_task_at_level (path, path.parts_length () - 1);
  auto sibling_index = path[path.parts_length () - 1];

  auto task = std::make_unique<Task> ();
  parent->add_child_after (sibling_index, std::move (task));
}

void
WBSImpl::indent (const Path & path)
{
  assert (path.empty () == false);
  assert (path.last_part () != 0);

  auto parent = get_task_at_level (path, path.parts_length () - 1);
  auto child_index = path[path.parts_length () - 1];

  parent->indent_child (child_index);
}

void
WBSImpl::unindent (const Path & path)
{
  assert (path.parts_length () > 1);

  size_t child_index = path[path.parts_length () - 1];
  size_t parent_index = path[path.parts_length () - 2];
  auto parent = get_task_at_level (path, path.parts_length () - 1);

  parent->unindent_child (child_index, parent_index);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
