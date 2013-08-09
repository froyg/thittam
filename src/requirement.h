/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__7c81bf88_fe59_11e2_934c_68a3c42125fd
#define HIPRO_THITTAM__7c81bf88_fe59_11e2_934c_68a3c42125fd

#include <memory>
#include <string>

class Requirement
{
public:
  typedef std::shared_ptr<Requirement> ptr_t;
  typedef std::weak_ptr<Requirement> weak_ptr_t;

public:
  virtual const std::string & id (void) const = 0;
  virtual const std::string & title (void) const = 0;
  virtual const std::string & description (void) const = 0;
  virtual Requirement::ptr_t parent (void) = 0;

  virtual void set_id (const std::string & id) = 0;
  virtual void set_title (const std::string & title) = 0;
  virtual void set_description (const std::string & description) = 0;
  virtual void set_parent (Requirement::ptr_t parent) = 0;

  virtual void add_child (Requirement::ptr_t child) = 0;
  virtual void remove_child (Requirement::ptr_t child) = 0;
  virtual void add_depends (Requirement::ptr_t depends) = 0;
  virtual void remove_depends (Requirement::ptr_t depends) = 0;

  /* virtual dtor */
  virtual ~Requirement () {}
};

#endif // HIPRO_THITTAM__7c81bf88_fe59_11e2_934c_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
