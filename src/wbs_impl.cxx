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
  : logger (logger),
    m_root (std::make_shared<Task> ())
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
  auto parent = m_root;
  for (size_t i = 0; i < (path.parts_length() - 1); ++i)
  {
    parent = parent->child (path[i]);
  }

  if (path.last_part () == ((int)parent->children_count () - 1))
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


std::shared_ptr<Task>
WBSImpl::get_task_at_level(const Path & path, size_t level)
{
  auto task = m_root;
  for (size_t i = 0; i < path.parts_length() and i < level; i++)
  {
    task = task->child (path[i]);
  }
  return task;
}

std::shared_ptr<Task>
WBSImpl::get_task (const Path& path)
{
  auto task = m_root;
  auto& parts = path.parts ();
  for (auto i : parts)
  {
    task = task->child (i);
  }
  return task;
}

std::shared_ptr<Task>
WBSImpl::add_child (const Path & path)
{
  auto parent = get_task (path);
  auto task = std::make_shared<Task> ();
  parent->add_child (task);
  return task;
}

std::shared_ptr<Task>
WBSImpl::add_sibling (const Path & path)
{
  ASSERT ((! path.empty ()), "Sibling path cannot be empty");

  auto parent = get_task_at_level (path, path.parts_length () - 1);
  auto sibling_index = path.last_part ();

  auto task = std::make_shared<Task> ();
  parent->add_child_after (sibling_index, task);
  return task;
}


NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
