/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "project-controller_impl.h"

NAMESPACE__THITTAM__START

ProjectControllerImpl::ProjectControllerImpl(hipro::log::Logger* logger)
  : logger(logger)
{

}

void
ProjectControllerImpl::view_wbs_selected(void)
{
  auto widget = m_wbs_controller->view_widget();
  m_view->attach_content(widget);
}

void
ProjectControllerImpl::view_resources_selected(void)
{
  auto widget = m_resources_controller->view_widget();
  m_view->attach_content(widget);
}

void
ProjectControllerImpl::view_gantt_selected(void)
{
  auto widget = m_gantt_controller->view_widget();
  m_view->attach_content(widget);
}

void
ProjectControllerImpl::view_resource_usage_selected(void)
{
  auto widget = m_resource_usage_controller->view_widget();
  m_view->attach_content(widget);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
