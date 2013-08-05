/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <boost/filesystem.hpp>

#include "main-view_impl.h"


MainViewImpl::MainViewImpl (HLogPtr logger,
                            Glib::RefPtr<Gtk::Builder> builder)
  : m_logger (logger)
{
  builder->get_widget ("main-window", m_window);
  m_window->signal_hide ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_close));

  m_window->show ();
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
