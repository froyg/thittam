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

#include <boost/signals2.hpp>

class Requirement
{
public:
  typedef std::shared_ptr<Requirement> ptr_t;

public:
  virtual std::string id (void) = 0;
  virtual std::string title (void) = 0;
  virtual std::string description (void) = 0;
  virtual int height (void) = 0;
  virtual void add_child (Requirement::ptr_t child) = 0;
  virtual void add_depends (Requirement::ptr_t depends) = 0;
  virtual void remove_child (Requirement::ptr_t child) = 0;

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
