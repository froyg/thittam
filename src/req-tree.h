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
#include <string>
#include <fstream>

#include <boost/signals2.hpp>

#include "requirement.h"

class ReqTree
{
public:
  typedef std::shared_ptr<ReqTree> ptr_t;

  /* This signal is raised when the tree has changed */
  typedef boost::signals2::signal <void (void)> signal_tree_dirty_t;

public:
  virtual signal_tree_dirty_t & signal_tree_dirty (void) = 0;

  /* Add the given child to the parent node. If parent node is nullptr
     then add it to the root node. If duplicate is true re-number the
     reqid's in the given child node tree and return the new reqid. */
  virtual std::string add_child (Requirement::ptr_t parent,
                                 Requirement::ptr_t new_req,
                                 bool duplicate) = 0;
  virtual std::string add_sibling (Requirement::ptr_t sibling,
                                   Requirement::ptr_t new_req,
                                   bool duplicate) = 0;

  /* move operations. Return true if the operation is successful */
  virtual bool up_sibling (Requirement::ptr_t req) = 0;
  virtual bool down_sibling (Requirement::ptr_t req) = 0;
  virtual bool up_level (Requirement::ptr_t req) = 0;
  virtual bool down_level (Requirement::ptr_t req) = 0;

  /* position check helpers */
  virtual bool is_first_sibling (Requirement::ptr_t req) = 0;
  virtual bool is_last_sibling (Requirement::ptr_t req) = 0;
  virtual bool is_top_level (Requirement::ptr_t req) = 0;
  virtual bool is_bottom_level (Requirement::ptr_t req) = 0;

  virtual int height (void) = 0;

  virtual Requirement::ptr_t get (const std::string & reqid) = 0;
  virtual void detach (Requirement::ptr_t node) = 0;

  virtual bool is_dirty (void) = 0;
  virtual void clear_dirty (void) = 0;

  /* populate the json string data */
  virtual void load (const std::string & data) = 0;
  /* populate the json data from the file handle */
  virtual void load (const std::ifstream & file) = 0;
  /* serialize the req-tree into json string */
  virtual std::string serialize (void) = 0;

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
