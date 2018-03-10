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

std::vector<Task *> &&
Task::children (void) const
{
  std::vector<Task *> children;
  children.reserve (m_children.size ());

  for (auto & child : m_children)
  {
    children.push_back (child.get ());
  }

  return std::move (children);
}

void
Task::add_child (std::unique_ptr<Task> && task)
{
  auto task_raw = task.get ();
  m_children.push_back (std::move (task));

  std::ostringstream os;
  os << m_id << "." << m_children.size ();
  task_raw->m_id = os.str ();
}

void
Task::add_child_after (const std::string & id, std::unique_ptr<Task> && task)
{
  for (auto it = m_children.begin (); it != m_children.end (); ++it)
  {
    auto & child = *it;
    if (child->id () == id)
    {
      it++;
      m_children.insert (it, std::move (task));
      renumber_id_of_children ();
      return;
    }
  }
}

void
Task::add_child_before (const std::string & id, std::unique_ptr<Task> && task)
{
  for (auto it = m_children.begin (); it != m_children.end (); ++it)
  {
    auto & child = *it;
    if (child->id () == id)
    {
      m_children.insert (it, std::move (task));
      renumber_id_of_children ();
      return;
    }
  }
}

void
Task::remove_child (const std::string & id)
{
  for (auto it = m_children.begin (); it != m_children.end (); ++it)
  {
    auto & child = *it;
    if (child->id () == id)
    {
      m_children.erase (it);
      renumber_id_of_children ();
      return;
    }
  }
}

void
Task::renumber_id_of_children (void)
{
  int current_id = 1;

  for (auto & child : m_children)
  {
    std::ostringstream os;
    os << m_id << "." << current_id;
    child->m_id = os.str ();
    current_id +=1 ;
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

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
