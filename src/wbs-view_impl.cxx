/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "wbs-view_impl.h"

NAMESPACE__THITTAM__START

WBSViewImpl::WBSViewImpl (
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder)
  : logger (logger)
{
  builder->get_widget ("main-window", m_main_window);
}

NAMESPACE__THITTAM__END
/*
  Local Variables:
  mode: c++
  End:
*/
