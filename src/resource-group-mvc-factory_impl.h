/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__71ebd5b2_27a8_11e9_9ace_448500dfb04c
#define HIPRO__71ebd5b2_27a8_11e9_9ace_448500dfb04c

#include "resource-group-mvc-factory.h"
#include "resource-group-view_impl.h"
#include "resource-group-controller_impl.h"

NAMESPACE__THITTAM__START

class ResourceGroupMVCFactoryImpl : public ResourceGroupMVCFactory
{
public:
  ResourceGroupMVCFactoryImpl (
    hipro::log::Logger* logger, Gtk::Window* main_window)
    : logger (logger),
      m_main_window (main_window)
  {

  }

  std::unique_ptr<ResourceGroupController> create (ResourceGroup* model)
  {
    auto controller = std::make_unique<ResourceGroupControllerImpl> (logger);
    auto ui = Gtk::Builder::create_from_resource (
      "/ui/resource-group-view.glade");
    auto view = std::make_unique<ResourceGroupViewImpl> (
      logger, ui, m_main_window);

    view->set_handler (controller.get ());
    controller->set_model (model);
    controller->set_view (std::move (view));
    return controller;
  }

private:
  hipro::log::Logger* logger = nullptr;
  Gtk::Window* m_main_window = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__71ebd5b2_27a8_11e9_9ace_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
