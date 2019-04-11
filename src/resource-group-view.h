/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__5bbeba98_27a8_11e9_ae30_448500dfb04c
#define HIPRO__5bbeba98_27a8_11e9_ae30_448500dfb04c

#include <string>

#include <gtkmm.h>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ResourceGroupViewCallbacks
{
public:
  virtual
  ~ResourceGroupViewCallbacks() {}

  virtual void
  view_group_name_changed(void) = 0;
  virtual void
  view_save_pressed(void) = 0;
  virtual void
  view_cancel_pressed(void) = 0;
};

class ResourceGroupView
{
public:
  virtual
  ~ResourceGroupView() {}

  virtual Gtk::Widget*
  widget(void) = 0;

  virtual void
  set_handler(ResourceGroupViewCallbacks* handler) = 0;

  virtual void
  enable_save(bool f) = 0;

  virtual void
  show(void) = 0;
  virtual void
  hide(void) = 0;

  virtual void
  set_name(const std::string& name) = 0;
  virtual void
  set_description(const std::string& description) = 0;

  virtual const std::string&
  name(void) const = 0;
  virtual const std::string&
  description(void) const = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__5bbeba98_27a8_11e9_ae30_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
