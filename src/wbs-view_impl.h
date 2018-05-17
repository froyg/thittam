/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__ea1bea38_59c5_11e8_892c_448500dfb04c
#define HIPRO__ea1bea38_59c5_11e8_892c_448500dfb04c

#include <gtkmm.h>

#include "wbs-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class WBSViewImpl : public WBSView
{
public:
  WBSViewImpl (hipro::log::Logger* logger, Glib::RefPtr<Gtk::Builder> builder);

  /*--- WBSView interface ---*/
  Gtk::Widget* widget (void)
  {
    return m_main_window;
  }

  void set_handler (WBSViewCallbacks* handler)
  {
    m_handler = handler;
  }

private:
  hipro::log::Logger* logger = nullptr;

  Gtk::Window* m_main_window = nullptr;
  WBSViewCallbacks* m_handler = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__ea1bea38_59c5_11e8_892c_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
