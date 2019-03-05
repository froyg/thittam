/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__944516ec_5a93_11e8_924a_448500dfb04c
#define HIPRO__944516ec_5a93_11e8_924a_448500dfb04c

#include <gtkmm.h>

#include "resource-usage-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourceUsageViewImpl : public ResourceUsageView
{
public:
  ResourceUsageViewImpl(
    hipro::log::Logger* logger,
    Glib::RefPtr<Gtk::Builder> builder);

  /*--- ResourceUsageView interface ---*/
  Gtk::Widget*
  widget(void)
  {
    return m_top_widget;
  }

  void
  set_handler(ResourceUsageViewCallbacks* handler)
  {
    m_handler = handler;
  }

private:
  hipro::log::Logger* logger = nullptr;

  Gtk::Widget* m_top_widget = nullptr;
  ResourceUsageViewCallbacks* m_handler = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__944516ec_5a93_11e8_924a_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
