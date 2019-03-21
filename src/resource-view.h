/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__a3a16b04_26d0_11e9_b5d8_448500dfb04c
#define HIPRO__a3a16b04_26d0_11e9_b5d8_448500dfb04c

#include <string>

#include <gtkmm.h>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ResourceViewCallbacks
{
public:
  virtual ~ResourceViewCallbacks () {}

  virtual void view_save_pressed (void) = 0;
  virtual void view_cancel_pressed (void) = 0;
};

class ResourceView
{
public:
  virtual ~ResourceView () {}

  virtual Gtk::Widget* widget (void) = 0;

  virtual void set_handler (ResourceViewCallbacks* handler) = 0;

  virtual void show (void) = 0;
  virtual void hide (void) = 0;

  virtual void set_short_name (const std::string& short_name) = 0;
  virtual void set_long_name (const std::string& long_name) = 0;
  virtual void set_cost (double cost) = 0;
  virtual void set_description (const std::string& description) = 0;

  virtual const std::string& short_name (void) const = 0;
  virtual const std::string& long_name (void) const = 0;
  virtual double cost (void) const = 0;
  virtual const std::string& description (void) const = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__a3a16b04_26d0_11e9_b5d8_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
