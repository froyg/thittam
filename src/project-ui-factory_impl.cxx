/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "project-ui-factory_impl.h"
#include "project-view_impl.h"
#include "project-controller_impl.h"
#include "wbs-view_impl.h"
#include "wbs-controller_impl.h"

NAMESPACE__THITTAM__START

ProjectUIFactoryImpl::ProjectUIFactoryImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

std::unique_ptr<ProjectController>
ProjectUIFactoryImpl::create (Project * project)
{
  auto project_ui = Gtk::Builder::create_from_resource (
    "/ui/project-view.glade");
  auto project_view = std::make_unique<ProjectViewImpl> (logger, project_ui);
  auto project_controller = std::make_unique<ProjectControllerImpl> (logger);

  auto wbs_ui = Gtk::Builder::create_from_resource (
    "/ui/wbs-view.glade");
  auto wbs_view = std::make_unique<WBSViewImpl> (logger, wbs_ui);
  auto wbs_controller = std::make_unique<WBSControllerImpl> (logger);

  project_view->set_handler (project_controller.get ());
  project_controller->set_view (std::move (project_view));

  wbs_view->set_handler (wbs_controller.get ());
  wbs_controller->set_view (std::move (wbs_view));

  project_controller->set_wbs_controller (std::move (wbs_controller));

  return project_controller;
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
