/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__981d4a46_5a93_11e8_a097_448500dfb04c
#define HIPRO__981d4a46_5a93_11e8_a097_448500dfb04c

#include "resource-usage-controller.h"
#include "resource-usage-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourceUsageControllerImpl
  : public ResourceUsageController, public ResourceUsageViewCallbacks
{
public:
  ResourceUsageControllerImpl(hipro::log::Logger* logger);
  ~ResourceUsageControllerImpl() {}

  /*--- DI ---*/
  void
  set_view(std::unique_ptr<ResourceUsageView> view)
  {
    m_view = std::move(view);
  }

  /*--- ResourceUsageController interface ---*/
  Gtk::Widget*
  view_widget(void)
  {
    return m_view->widget();
  }

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<ResourceUsageView> m_view;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__981d4a46_5a93_11e8_a097_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
