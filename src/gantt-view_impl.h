/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__31be810e_5a91_11e8_9b51_448500dfb04c
#define HIPRO__31be810e_5a91_11e8_9b51_448500dfb04c

#include <gtkmm.h>

#include "gantt-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class GANTTViewImpl : public GANTTView
{
public:
  GANTTViewImpl(hipro::log::Logger* logger, Glib::RefPtr<Gtk::Builder> builder);

  /*--- GANTTView interface ---*/
  Gtk::Widget*
  widget(void)
  {
    return m_top_widget;
  }

  void
  set_handler(GANTTViewCallbacks* handler)
  {
    m_handler = handler;
  }

private:
  hipro::log::Logger* logger = nullptr;

  Gtk::Widget* m_top_widget = nullptr;
  GANTTViewCallbacks* m_handler = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__31be810e_5a91_11e8_9b51_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
