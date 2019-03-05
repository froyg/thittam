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
#include <ostream>

#include <boost/property_tree/ptree.hpp>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class Task
{
public:
  const std::string&
  id(void) const
  {
    return m_id;
  }

  const std::string&
  title(void) const
  {
    return m_title;
  }

  void
  set_title(const std::string& title)
  {
    m_title = title;
  }

  const std::string&
  description(void) const
  {
    return m_description;
  }

  void
  set_description(const std::string& description)
  {
    m_description = description;
  }

  const std::string&
  work(void) const
  {
    return m_work;
  }

  int
  work_in_minutes(void) const
  {
    return m_work_in_minutes;
  }

  void
  set_work(const std::string& work);

  Task*
  parent(void) const
  {
    return m_parent;
  }

  void
  set_parent(Task* parent)
  {
    m_parent = parent;
  }

  bool
  has_children(void) const
  {
    return (m_children_raw.empty() != true);
  }

  Task*
  child(size_t index)
  {
    return m_children_raw[index];
  }

  size_t
  children_count(void) const
  {
    return m_children_raw.size();
  }

  const std::vector<Task*>&
  children(void) const
  {
    return m_children_raw;
  }

  void
  add_child(std::unique_ptr<Task>&& task);
  void
  add_child_after(size_t index, std::unique_ptr<Task>&& task);
  void
  remove_child(size_t index);
  void
  indent_child(size_t index);
  void
  unindent_child(size_t index, size_t parent_index);

  boost::property_tree::ptree
  dump(void);

private:
  void
  recompute_id_of_children(size_t start_index = 0);
  std::string
  compute_child_id(int number) const;

private:
  std::string m_id;
  std::string m_title;
  std::string m_description;
  std::string m_work;
  int m_work_in_minutes;

  Task* m_parent = nullptr;
  std::vector<Task*> m_children_raw;
  std::vector<std::unique_ptr<Task>> m_children_owned;

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
