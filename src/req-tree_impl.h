/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__a0055c6a_00db_11e3_ae98_68a3c42125fd
#define HIPRO_THITTAM__a0055c6a_00db_11e3_ae98_68a3c42125fd

#include <memory>

#include <boost/signals2.hpp>

#include "common.h"
#include "req-tree.h"

class ReqTreeImpl : public ReqTree
{
public:
  typedef std::shared_ptr<ReqTreeImpl> ptr_t;

public:
  /* ----------- ctor/dtor ------------- */
  ReqTreeImpl (HLogPtr logger);
  ~ReqTreeImpl () {}

  /* ----------- methods required by the interface --------- */
  signal_tree_dirty_t & signal_tree_dirty (void)
  {
    return m_signal_tree_dirty;
  }

  std::string add_child (Requirement::ptr_t parent,
                         Requirement::ptr_t new_req, bool duplicate);
  std::string add_sibling (Requirement::ptr_t sibling,
                           Requirement::ptr_t new_req, bool duplicate);

  bool up_sibling (Requirement::ptr_t req);
  bool down_sibling (Requirement::ptr_t req);
  bool up_level (Requirement::ptr_t req);
  bool down_level (Requirement::ptr_t req);

  bool is_first_sibling (Requirement::ptr_t req);
  bool is_last_sibling (Requirement::ptr_t req);
  bool is_top_level (Requirement::ptr_t req);
  bool is_bottom_level (Requirement::ptr_t req);

  int height (void);

  Requirement::ptr_t get (const std::string & reqid);
  void detach (Requirement::ptr_t node);

  bool is_dirty (void);
  void clear_dirty (void);

  void load (const std::string & data);
  void load (const std::ifstream & file);
  std::string serialize (void);

private:
  HLogPtr m_logger;
  signal_tree_dirty_t m_signal_tree_dirty;
  int m_last_id;
  bool m_dirty;
};


#endif // HIPRO_THITTAM__a0055c6a_00db_11e3_ae98_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
