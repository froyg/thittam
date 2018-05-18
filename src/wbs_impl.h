/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__e34e71d0_2450_11e8_92c3_448500dfb04c
#define HIPRO__e34e71d0_2450_11e8_92c3_448500dfb04c

#include <list>

#include "_namespace.h"
#include "wbs.h"
#include "log.h"
#include "task.h"

NAMESPACE__THITTAM__START

class WBSEntry
{
public:
  WBSEntry (const WBS::Path & path_, std::unique_ptr<Task> && task_)
    : path (path_),
      task (std::move (task_))
  {

  }

  WBS::Path path;
  std::unique_ptr<Task> task;
};


class WBSImpl : public WBS
{
public:
  WBSImpl (hipro::log::Logger* logger);
  ~WBSImpl () {}

  /*--- DI ---*/
  void add_observer (WBSObserver * observer)
  {
    m_observers.push_back (observer);
  }

  /*--- WBS interface ---*/
  bool is_first_child (const Path & path) const;
  bool is_last_child (const Path & path) const;
  bool is_top_level (const Path & path) const;

  void add_child (const Path & parent_path);
  void add_sibling (const Path & path);

  bool dirty (void) const
  {
    return m_dirty;
  }

  void clear_dirty (void)
  {
    m_dirty = false;
  }

private:
  void notify_observers_node_inserted (const WBS::Path & path);
  void notify_observers_node_changed (const WBS::Path & path);
  void notify_observers_node_deleted (const WBS::Path & path);
  void notify_observers_node_reordered (
    const WBS::Path & path, const std::vector<int> & new_order);

private:
  hipro::log::Logger* logger = nullptr;
  bool m_dirty = false;

  Task m_root;
  typedef WBSEntry Entry;
  std::list<Entry> m_flat_wbs;
  std::vector<WBSObserver *> m_observers;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e34e71d0_2450_11e8_92c3_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
