/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__9f2aa1b2_fe59_11e2_8d34_68a3c42125fd
#define HIPRO_THITTAM__9f2aa1b2_fe59_11e2_8d34_68a3c42125fd

#include <memory>

#include <boost/signals2.hpp>

#include "requirement.h"

class ReqTree
{
public:
  typedef std::shared_ptr<ReqTree> ptr_t;

  /* This signal is raised when the tree has changed */
  typedef boost::signals2::signal <void (void)> signal_tree_dirty_t;

public:
  /* Add the given child to the parent node. If parent node is nullptr
     then add it to the root node. If duplicate is true re-number the
     reqid's in the given child node tree and add it. If the operation
     was successful return true */
  virtual bool add_child (Requirement::ptr_t child,
                          Requirement::ptr_t parent,
                          bool duplicate) = 0;
  virtual bool add_sibling (Requirement::ptr_t sibling,
                            Requirement::ptr_t new_node,
                            bool duplicate) = 0;

  /* Move a node up in the same level. Return true if the operation is
     successful */
  virtual bool move_node_up (Requirement::ptr_t node) = 0;
  virtual bool move_node_down (Requirement::ptr_t node) = 0;
  virtual bool indent_node_left (Requirement::ptr_t node) = 0;
  virtual bool indent_node_right (Requirement::ptr_t node) = 0;

  virtual Requirement::ptr_t get_requirement (const std::string & reqid) = 0;
  virtual void detach_node (Requirement::ptr_t node) = 0;

  virtual bool is_dirty (void) = 0;

  /* virtual dtor */
  virtual ~ReqTree () {}
};


#endif // HIPRO_THITTAM__9f2aa1b2_fe59_11e2_8d34_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
