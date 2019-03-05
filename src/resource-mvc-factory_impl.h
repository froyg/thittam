/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__e0897216_27a0_11e9_a24a_448500dfb04c
#define HIPRO__e0897216_27a0_11e9_a24a_448500dfb04c

#include "resource-mvc-factory.h"
#include "resource-view_impl.h"
#include "resource-controller_impl.h"

NAMESPACE__THITTAM__START

class ResourceMVCFactoryImpl : public ResourceMVCFactory
{
public:
  ResourceMVCFactoryImpl(
    hipro::log::Logger* logger, Gtk::Window* main_window)
    : logger(logger),
      m_main_window(main_window)
  {

  }

  std::unique_ptr<ResourceController>
  create(Resource* model)
  {
    auto controller = std::make_unique<ResourceControllerImpl> (logger);
    auto ui = Gtk::Builder::create_from_resource("/ui/resource-view.glade");
    auto view = std::make_unique<ResourceViewImpl> (logger, ui, m_main_window);

    view->set_handler(controller.get());
    controller->set_model(model);
    controller->set_view(std::move(view));
    return controller;
  }

private:
  hipro::log::Logger* logger = nullptr;
  Gtk::Window* m_main_window = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e0897216_27a0_11e9_a24a_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
