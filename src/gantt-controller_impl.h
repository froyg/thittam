/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__36c87f10_5a91_11e8_ae8f_448500dfb04c
#define HIPRO__36c87f10_5a91_11e8_ae8f_448500dfb04c

#include "gantt-controller.h"
#include "gantt-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class GANTTControllerImpl : public GANTTController, public GANTTViewCallbacks
{
public:
  GANTTControllerImpl (hipro::log::Logger* logger);
  ~GANTTControllerImpl () {}

  /*--- DI ---*/
  void set_view (std::unique_ptr<GANTTView> view)
  {
    m_view = std::move (view);
  }

  /*--- GANTTController interface ---*/
  Gtk::Widget * view_widget (void)
  {
    return m_view->widget ();
  }

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<GANTTView> m_view;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__36c87f10_5a91_11e8_ae8f_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
