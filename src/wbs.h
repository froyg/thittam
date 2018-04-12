/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__e1c5e618_2450_11e8_9023_448500dfb04c
#define HIPRO__e1c5e618_2450_11e8_9023_448500dfb04c

#include "_namespace.h"
#include "task.h"

NAMESPACE__THITTAM__START

typedef Task::Path WBSPath;

class WBSObserver
{
public:
  virtual void wbs_observer_node_inserted (const WBSPath & path) = 0;
  virtual void wbs_observer_node_changed (const WBSPath & path) = 0;
  virtual void wbs_observer_node_deleted (const WBSPath & path) = 0;
  virtual void wbs_observer_node_reordered (
    const WBSPath & path, const std::vector<int> & new_order) = 0;
};

class WBS
{
public:
  typedef WBSPath Path;

public:
  virtual ~WBS () {}

  virtual bool is_first_child (const Path & path) const = 0;
  virtual bool is_last_child (const Path & path) const = 0;
  virtual bool is_top_level (const Path & path) const = 0;

  virtual void add_child (const Path & parent_path) = 0;
  virtual void add_sibling (const Path & path) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e1c5e618_2450_11e8_9023_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
