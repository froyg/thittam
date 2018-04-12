/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "task.h"
#include "util.h"

NAMESPACE__THITTAM__START

void
Task::set_work (const std::string & work)
{
  auto minutes = util::effort_str_to_minutes (
    work, m_working_days_per_week, m_working_hours_per_day);
  if (minutes < 0)
  {
    m_work = "1d";
    m_work_in_minutes = (m_working_hours_per_day * 60);
  }
  else
  {
    m_work = work;
    m_work_in_minutes = minutes;
  }
}

const Task::Path &
Task::add_child (Task * task)
{
  auto child_index = m_children.size ();
  m_children.push_back (task);
  task->m_id = compute_child_id (child_index);
  task->m_path = compute_child_path (child_index);
  return task->path ();
}

void
Task::add_child_after (
  size_t index, Task * task,
  std::function<void (const Task::Path &)> & change_notification)
{
  auto add_it = m_children.begin () + index + 1;
  m_children.insert (add_it, task);

  recompute_path_and_id_of_children (index + 1);

  auto changed_it = m_children.begin () + index + 1;
  for (auto it = changed_it; it != m_children.end (); ++it)
  {
    notify_change_in_tree (*it, change_notification);
  }
}

void
Task::remove_child (
  size_t index,
  std::function<void (const Task::Path&)> & change_notification)
{
  auto remove_it = m_children.begin () + index;
  m_children.erase (remove_it);

  recompute_path_and_id_of_children (index);

  auto changed_it = m_children.begin () + index;
  for (auto it = changed_it; it != m_children.end (); ++it)
  {
    notify_change_in_tree (*it, change_notification);
  }
}

boost::property_tree::ptree
Task::dump (void)
{
    boost::property_tree::ptree pt;
    pt.put ("id", m_id);
    pt.put ("title", m_title);
    pt.put ("description", m_description);
    pt.put ("work", m_work);

    boost::property_tree::ptree child_array;
    for (auto & child : m_children)
      {
        child_array.push_back
          (std::make_pair ("", boost::property_tree::ptree(child->id ())));
      }
    pt.put_child ("children", child_array);
    return pt;
}

void
Task::recompute_path_and_id_of_children (size_t start_index)
{
  auto begin_it = m_children.begin () + start_index;
  auto index = start_index;
  for (auto it = begin_it; it != m_children.end (); ++it)
  {
    recompute_path_and_id_of_tree (*it, index);
    index += 1;
  }
}

void
Task::recompute_path_and_id_of_tree (Task * task, size_t index)
{
  task->m_id = compute_child_id (index);
  task->m_path = compute_child_path (index);

  if (task->has_children ())
  {
    size_t child_index = 0;
    for (auto child : m_children)
    {
      recompute_path_and_id_of_tree (child, child_index);
      child_index += 1;
    }
  }
}

std::string &&
Task::compute_child_id (int index)
{
  std::ostringstream os;
  size_t part = index + 1;
  if (m_parent == nullptr)
  {
    os << part;
  }
  else
  {
    os << m_id << "." << part;
  }

  return std::move (os.str ());
}

Task::Path &&
Task::compute_child_path (int number)
{
  Task::Path path;
  if (m_parent == nullptr)
  {
    path.push_back (number);
  }
  else
  {
    path = m_parent->path ();
    path.push_back (number);
  }

  return std::move (path);
}

void
Task::notify_change_in_tree (
  Task * task,
  std::function<void (const Task::Path &)> & change_notification)
{
  change_notification (task->path ());
  for (auto child : task->m_children)
  {
    change_notification (child->path ());
  }
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
