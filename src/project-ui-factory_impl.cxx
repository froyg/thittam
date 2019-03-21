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
#include "wbs_impl.h"
#include "resources-view_impl.h"
#include "resources-controller_impl.h"
#include "resource-manager.h"
#include "gantt-view_impl.h"
#include "gantt-controller_impl.h"
#include "resource-usage-view_impl.h"
#include "resource-usage-controller_impl.h"
#include "resource-mvc-factory_impl.h"
#include "resource-group-mvc-factory_impl.h"

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
  auto wbs = std::make_unique<WBSImpl> (logger);

  auto resource_group_mvc_factory =
    std::make_unique<ResourceGroupMVCFactoryImpl> (logger, m_parent_window);
  auto resource_mvc_factory = std::make_unique<ResourceMVCFactoryImpl> (
    logger, m_parent_window);
  auto resources_ui = Gtk::Builder::create_from_resource (
    "/ui/resources-view.glade");
  auto resources_view =
    std::make_unique<ResourcesViewImpl> (logger, resources_ui);
  auto resources_controller = std::make_unique<ResourcesControllerImpl> (
    logger, std::move (resource_mvc_factory),
    std::move (resource_group_mvc_factory));
  auto resource_manager = std::make_unique<ResourceManager> ();

  auto gantt_ui = Gtk::Builder::create_from_resource (
    "/ui/gantt-view.glade");
  auto gantt_view = std::make_unique<GANTTViewImpl> (logger, gantt_ui);
  auto gantt_controller = std::make_unique<GANTTControllerImpl> (logger);

  auto resource_usage_ui = Gtk::Builder::create_from_resource (
    "/ui/resource-usage-view.glade");
  auto resource_usage_view =
    std::make_unique<ResourceUsageViewImpl> (logger, resource_usage_ui);
  auto resource_usage_controller =
    std::make_unique<ResourceUsageControllerImpl> (logger);

  project_view->set_handler (project_controller.get ());
  project_controller->set_view (std::move (project_view));

  wbs_view->set_handler (wbs_controller.get ());
  wbs_controller->set_view (std::move (wbs_view));
  wbs_controller->set_wbs (wbs.get ());

  resources_view->set_handler (resources_controller.get ());
  resources_controller->set_view (std::move (resources_view));
  resources_controller->set_rm (std::move (resource_manager));

  gantt_view->set_handler (gantt_controller.get ());
  gantt_controller->set_view (std::move (gantt_view));

  resource_usage_view->set_handler (resource_usage_controller.get ());
  resource_usage_controller->set_view (std::move (resource_usage_view));

  project_controller->set_wbs (std::move (wbs));
  project_controller->set_wbs_controller (std::move (wbs_controller));
  project_controller->set_resources_controller (
    std::move (resources_controller));
  project_controller->set_gantt_controller (std::move (gantt_controller));
  project_controller->set_resource_usage_controller (
    std::move (resource_usage_controller));

  project_controller->show_wbs ();

  return project_controller;
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
