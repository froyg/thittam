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
  /* This signal is raised when the tree has changed */
  typedef boost::signals2::signal <void (void)> signal_tree_dirty_t;

public:
  virtual signal_tree_dirty_t & signal_tree_dirty (void) = 0;

  /* Add the given child to the parent node. If parent node is nullptr
   * then add it to the root node. These methods generate a new reqid
   * and set it in the 'new_req'. */
  virtual std::string add_new_child (
    std::shared_ptr<Requirement> parent,
    std::shared_ptr<Requirement> new_req) = 0;
  virtual std::string add_new_sibling (
    std::shared_ptr<Requirement> sibling,
    std::shared_ptr<Requirement> new_req) = 0;

  /* Add the given child to the parent node. If parent node is nullptr
   * then add it to the root node. This method assumes that the given
   * Requirement object has a valid reqid. */
  virtual std::string add_child (
    std::shared_ptr<Requirement> parent,
    std::shared_ptr<Requirement> req) = 0;

  /* Renumber ID's of child requirement recursively and it to the
   * given parent and return the newly created child requirement's
   * shared pointer */
  virtual std::shared_ptr<Requirement> add_duplicate_child (
    std::shared_ptr<Requirement> parent,
    std::shared_ptr<Requirement> child) = 0;

  /* Detach the given node and its sub-tree from the ReqTree */
  virtual void detach (std::shared_ptr<Requirement> node) = 0;

  /* Methods to check the position of a Requirement object in the
   * "requirement tree" */
  virtual bool is_first_child (
    std::shared_ptr<const Requirement> req) const = 0;
  virtual bool is_last_child (
    std::shared_ptr<const Requirement> req) const = 0;
  virtual bool is_top_level (
    std::shared_ptr<const Requirement> req) const = 0;

  /* Move operations. It is an error if the requested 'Requirement'
   * cannot be moved. The caller should use the is_*() methods to make
   * sure the operation is possible */
  virtual void up_child (std::shared_ptr<Requirement> req) = 0;
  virtual void down_child (std::shared_ptr<Requirement> req) = 0;
  virtual void up_level (std::shared_ptr<Requirement> req) = 0;
  virtual void down_level (std::shared_ptr<Requirement> req) = 0;

  /* Methods to walk the tree */
  virtual size_t height (void) const = 0;
  virtual std::shared_ptr<Requirement> get (
    const std::string & reqid) const = 0;
  virtual std::shared_ptr<Requirement> root (void) const = 0;

  /* Manage the dirty flag */
  virtual bool is_dirty (void) const = 0;
  virtual void clear_dirty (void) = 0;
  virtual void set_dirty (void) = 0;

  /* populate the json string data */
  virtual void load (const std::string & data) = 0;
  /* populate the json data from the file handle */
  virtual void load (std::ifstream & file) = 0;
  /* serialize the req-tree into json string */
  virtual std::string serialize (void) = 0;

  /* virtual dtor */
  virtual ~ReqTree () {}
};

class ReqTreeFactory
{
public:
  virtual std::shared_ptr<ReqTree> create (void) = 0;
};

#endif // HIPRO_THITTAM__9f2aa1b2_fe59_11e2_8d34_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  End:
*/
