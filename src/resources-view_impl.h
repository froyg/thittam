/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__0da5375c_5a93_11e8_a301_448500dfb04c
#define HIPRO__0da5375c_5a93_11e8_a301_448500dfb04c

#include <gtkmm.h>

#include "resources-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourcesViewImpl : public ResourcesView
{
public:
  ResourcesViewImpl (
    hipro::log::Logger* logger, Glib::RefPtr<Gtk::Builder> builder);

  /*--- ResourcesView interface ---*/
  Gtk::Widget* widget (void)
  {
    return m_top_widget;
  }

  void set_handler (ResourcesViewCallbacks* handler)
  {
    m_handler = handler;
  }

private:
  hipro::log::Logger* logger = nullptr;

  Gtk::Widget* m_top_widget = nullptr;
  ResourcesViewCallbacks* m_handler = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__0da5375c_5a93_11e8_a301_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
