/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c
#define HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

#include <string>
#include <memory>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class TaskPath
{
public:
  TaskPath () : m_parts(10)
  {
  }

  TaskPath (const TaskPath & other)
  {
    m_parts = other.m_parts;
  }

  TaskPath (TaskPath && other)
  {
    m_parts = std::move (other.m_parts);
  }

  const std::vector<int> & parts (void) const
  {
    return m_parts;
  }

  void push_back (int index)
  {
    m_parts.push_back (index);
  }

  size_t parts_length (void) const
  {
    return m_parts.size ();
  }

  void operator= (const TaskPath & other)
  {
    m_parts = other.parts ();
  }

  bool operator== (const TaskPath & right) const
  {
    return m_parts == right.parts ();
  }

private:
  std::vector<int> m_parts;
};


class Task
{
public:
  typedef TaskPath Path;

public:
  const Path & path (void) const
  {
    return m_path;
  }

  const std::string & id (void) const
  {
    return m_id;
  }

  const std::string & title (void) const
  {
    return m_title;
  }

  void set_title (const std::string & title)
  {
    m_title = title;
  }

  const std::string & description (void) const
  {
    return m_description;
  }

  void set_description (const std::string & description)
  {
    m_description = description;
  }

  const std::string & work (void) const
  {
    return m_work;
  }

  int work_in_minutes (void) const
  {
    return m_work_in_minutes;
  }

  void set_work (const std::string & work);

  Task * parent (void) const
  {
    return m_parent;
  }

  void set_parent (Task * parent)
  {
    m_parent = parent;
  }

  bool has_children (void) const
  {
    return (m_children.empty () != true);
  }

  Task * child (size_t index)
  {
    return m_children[index];
  }

  size_t children_count (void) const
  {
    return m_children.size ();
  }

  const std::vector<Task *> & children (void) const
  {
    return m_children;
  }

  const Task::Path & add_child (Task * task);

  void add_child_after (
    size_t index, Task * task,
    std::function<void (const Task::Path &)> insert_notification,
    std::function<void (const Task::Path &)> change_notification);

  void remove_child (
    size_t index,
    std::function<void (const Task::Path&)> remove_notification,
    std::function<void (const Task::Path &)> change_notification);

  boost::property_tree::ptree dump (void);

private:
  void recompute_path_and_id_of_children (size_t start_index);
  void recompute_path_and_id_of_tree (Task * task, size_t index);
  std::string && compute_child_id (int number);
  Path && compute_child_path (int number);
  void notify_change_in_tree (
    Task * task,
    std::function<void (const Task::Path &)> change_notification);

private:
  Path m_path;
  std::string m_id;
  std::string m_title;
  std::string m_description;
  std::string m_work;
  int m_work_in_minutes;

  Task * m_parent = nullptr;
  std::vector<Task *> m_children;

  const int m_working_days_per_week = 0;
  const int m_working_hours_per_day = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
