/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__09fb1f80_2ac4_11e8_8457_448500dfb04c
#define HIPRO__09fb1f80_2ac4_11e8_8457_448500dfb04c

#include <gtkmm.h>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class WBSController
{
public:
  virtual
  ~WBSController() {}

  virtual Gtk::Widget*
  view_widget(void) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__09fb1f80_2ac4_11e8_8457_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
