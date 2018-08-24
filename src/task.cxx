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

void
Task::add_child (std::unique_ptr<Task> && task)
{
  auto task_raw = task.get ();
  auto child_index = m_children_raw.size ();
  m_children_raw.push_back(task_raw);
  m_children_owned.push_back (std::move (task));

  task_raw->set_parent (this);
  task_raw->m_id = compute_child_id (child_index);
}

void
Task::add_child_after (size_t index, std::unique_ptr<Task> && task)
{
  auto task_raw = task.get ();
  auto raw_it = m_children_raw.begin () + index + 1;
  auto owned_it = m_children_owned.begin () + index + 1;

  m_children_raw.insert (raw_it, task_raw);
  m_children_owned.insert (owned_it, std::move (task));

  task_raw->set_parent (this);
  recompute_id_of_children (index + 1);
}

void
Task::remove_child (size_t index)
{
  auto raw_it = m_children_raw.begin () + index;
  auto owned_it = m_children_owned.begin () + index;

  m_children_raw.erase (raw_it);
  m_children_owned.erase (owned_it);

  recompute_id_of_children (index);
}

void
Task::indent_child (size_t index)
{
  assert(index != 0);
  auto new_parent = m_children_raw[index - 1];
  auto raw_it = m_children_raw.begin () + index;
  auto owned_it = m_children_owned.begin () + index;

  auto task = std::move (*owned_it);

  m_children_raw.erase (raw_it);
  m_children_owned.erase (owned_it);

  new_parent->add_child (std::move (task));
}

void
Task::unindent_child (size_t index, size_t parent_index)
{
  assert (m_parent != nullptr);
  auto new_parent = m_parent;
  auto raw_it = m_children_raw.begin () + index;
  auto owned_it = m_children_owned.begin () + index;

  auto task = std::move (*owned_it);

  m_children_raw.erase (raw_it);
  m_children_owned.erase (owned_it);

  new_parent->add_child_after (parent_index, std::move (task));
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
    for (auto & child : m_children_raw)
      {
        child_array.push_back
          (std::make_pair ("", boost::property_tree::ptree(child->id ())));
      }
    pt.put_child ("children", child_array);
    return pt;
}

void
Task::recompute_id_of_children (size_t start_index)
{
  auto begin_it = m_children_raw.begin () + start_index;
  auto index = start_index;
  for (auto it = begin_it; it != m_children_raw.end (); ++it)
  {
    recompute_id_of_tree (*it, index);
    index += 1;
  }
}

void
Task::recompute_id_of_tree (Task * task, size_t index)
{
  task->m_id = compute_child_id (index);

  if (task->has_children ())
  {
    size_t child_index = 0;
    for (auto child : m_children_raw)
    {
      recompute_id_of_tree (child, child_index);
      child_index += 1;
    }
  }
}

std::string
Task::compute_child_id (int index) const
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

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
