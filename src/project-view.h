/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__e3560f7c_438f_11e8_83c5_448500dfb04c
#define HIPRO__e3560f7c_438f_11e8_83c5_448500dfb04c

#include <gtkmm.h>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ProjectViewCallbacks
{
public:
  virtual void
  view_wbs_selected(void) = 0;
  virtual void
  view_resources_selected(void) = 0;
  virtual void
  view_gantt_selected(void) = 0;
  virtual void
  view_resource_usage_selected(void) = 0;
};

class ProjectView
{
public:
  virtual
  ~ProjectView() {}

  virtual Gtk::Widget*
  widget(void) = 0;

  virtual void
  set_handler(ProjectViewCallbacks* handler) = 0;
  virtual void
  attach_content(Gtk::Widget* widget) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e3560f7c_438f_11e8_83c5_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
