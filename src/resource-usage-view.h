/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__928531c0_5a93_11e8_b222_448500dfb04c
#define HIPRO__928531c0_5a93_11e8_b222_448500dfb04c

#include <gtkmm.h>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ResourceUsageViewCallbacks
{
public:
  virtual
  ~ResourceUsageViewCallbacks() {}

};

class ResourceUsageView
{
public:
  virtual
  ~ResourceUsageView() {}

  virtual Gtk::Widget*
  widget(void) = 0;

  virtual void
  set_handler(ResourceUsageViewCallbacks* handler) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__928531c0_5a93_11e8_b222_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
