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
Task::add_child (std::shared_ptr<Task> task)
{
  auto child_index = m_children.size ();
  m_children.push_back (task);

  task->set_parent (this);
  task->m_id = compute_child_id (child_index);
}

void
Task::add_child_after (size_t index, std::shared_ptr<Task> task)
{
  auto it = m_children.begin () + index + 1;

  m_children.insert (it, task);

  task->set_parent (this);
  recompute_id_of_children (index);
}

void
Task::remove_child (size_t index)
{
  auto it = m_children.begin () + index;

  m_children.erase (it);
  recompute_id_of_children (index);
}

void
Task::remove_child (std::shared_ptr<Task> task)
{
  size_t index = 0;
  for (auto it = m_children.begin (); it != m_children.end (); ++it)
  {
    index += 1;
    if (*it == task)
    {
      m_children.erase (it);
      break;
    }
  }

  recompute_id_of_children (index);
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
Task::recompute_id_of_children (size_t start_index)
{
  for (size_t i = start_index; i < m_children.size (); ++i)
  {
    m_children[i]->m_id = compute_child_id (i);
    m_children[i]->recompute_id_of_children ();
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
