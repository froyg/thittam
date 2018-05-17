/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__0bd01c5c_2ac4_11e8_ab38_448500dfb04c
#define HIPRO__0bd01c5c_2ac4_11e8_ab38_448500dfb04c

#include "wbs-controller.h"
#include "wbs-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class WBSControllerImpl : public WBSController, public WBSViewCallbacks
{
public:
  WBSControllerImpl (hipro::log::Logger* logger);
  ~WBSControllerImpl () {}

  /*--- DI ---*/
  void set_view (std::unique_ptr<WBSView> view)
  {
    m_view = std::move (view);
  }

  /*--- WBSController interface ---*/
  Gtk::Widget * view_widget (void)
  {
    return m_view->widget ();
  }

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<WBSView> m_view;
};

NAMESPACE__THITTAM__END


#endif // HIPRO__0bd01c5c_2ac4_11e8_ab38_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
