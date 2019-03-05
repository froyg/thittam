/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__c660c26a_544a_11e8_8d7f_448500dfb04c
#define HIPRO__c660c26a_544a_11e8_8d7f_448500dfb04c

#include "_namespace.h"
#include "project-controller.h"
#include "project-view.h"
#include "wbs.h"
#include "wbs-controller.h"
#include "resources-controller.h"
#include "gantt-controller.h"
#include "resource-usage-controller.h"
#include "log.h"


NAMESPACE__THITTAM__START

class ProjectControllerImpl : public ProjectController,
  public ProjectViewCallbacks
{
public:
  ProjectControllerImpl(hipro::log::Logger* logger);
  ~ProjectControllerImpl() {}

  /*--- DI ---*/
  void
  set_wbs_controller(std::unique_ptr<WBSController> controller)
  {
    m_wbs_controller = std::move(controller);
  }

  void
  set_resources_controller(
    std::unique_ptr<ResourcesController> controller)
  {
    m_resources_controller = std::move(controller);
  }

  void
  set_gantt_controller(std::unique_ptr<GANTTController> controller)
  {
    m_gantt_controller = std::move(controller);
  }

  void
  set_resource_usage_controller(
    std::unique_ptr<ResourceUsageController> controller)
  {
    m_resource_usage_controller = std::move(controller);
  }

  void
  set_view(std::unique_ptr<ProjectView> view)
  {
    m_view = std::move(view);
  }

  void
  set_wbs(std::unique_ptr<WBS> wbs)
  {
    m_wbs = std::move(wbs);
  }

  /*--- ProjectController interface ---*/
  Gtk::Widget*
  view_widget(void)
  {
    return m_view->widget();
  }

  void
  show_wbs(void)
  {
    view_wbs_selected();
  }

  /*--- ProjectViewCallbacks interface ---*/
  void
  view_wbs_selected(void);
  void
  view_resources_selected(void);
  void
  view_gantt_selected(void);
  void
  view_resource_usage_selected(void);

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<WBS> m_wbs;
  std::unique_ptr<WBSController> m_wbs_controller;
  std::unique_ptr<ResourcesController> m_resources_controller;
  std::unique_ptr<GANTTController> m_gantt_controller;
  std::unique_ptr<ResourceUsageController> m_resource_usage_controller;

  std::unique_ptr<ProjectView> m_view;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__c660c26a_544a_11e8_8d7f_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
