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

class WBSImpl : public WBS
{
public:
  WBSImpl (hipro::log::Logger* logger);
  ~WBSImpl () {}

  /*--- WBS interface ---*/
  bool is_first_child (const Path & path) const;
  bool is_last_child (const Path & path) const;
  bool is_top_level (const Path & path) const;

  void add_child (const Path & parent_path);
  void add_sibling (const Path & path);
  void indent (const Path & path);
  void unindent (const Path & path);

  Task* get_task_at_level(const Path & path, size_t level);
  Task* get_task (const Path& path);

  bool dirty (void) const
  {
    return m_dirty;
  }

  void clear_dirty (void)
  {
    m_dirty = false;
  }

private:
  hipro::log::Logger* logger = nullptr;
  bool m_dirty = false;

  Task m_root;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e34e71d0_2450_11e8_92c3_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
