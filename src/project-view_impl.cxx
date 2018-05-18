/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "project-view_impl.h"

NAMESPACE__THITTAM__START

ProjectViewImpl::ProjectViewImpl (
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder)
  : logger (logger)
{
  builder->get_widget ("top-widget", m_top_widget);
  auto parent = m_top_widget->get_parent ();
  if (parent)
  {
    parent->remove (*m_top_widget);
  }

  builder->get_widget ("container", m_container);

  Gtk::Button* btn;
  builder->get_widget ("btn-wbs", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &ProjectViewImpl::cb_on_wbs_clicked));

  builder->get_widget ("btn-resources", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &ProjectViewImpl::cb_on_resources_clicked));

  builder->get_widget ("btn-gantt", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &ProjectViewImpl::cb_on_gantt_clicked));

  builder->get_widget ("btn-resource-usage", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &ProjectViewImpl::cb_on_resource_usage_clicked));
}

void
ProjectViewImpl::cb_on_wbs_clicked (void)
{
  m_handler->view_wbs_selected ();
}

void
ProjectViewImpl::cb_on_resources_clicked (void)
{
  m_handler->view_resources_selected ();
}

void
ProjectViewImpl::cb_on_gantt_clicked (void)
{
  m_handler->view_gantt_selected ();
}

void
ProjectViewImpl::cb_on_resource_usage_clicked (void)
{
  m_handler->view_resource_usage_selected ();
}

void
ProjectViewImpl::attach_content (Gtk::Widget* widget)
{
  auto children = m_container->get_children ();
  for (auto child : children)
  {
    m_container->remove (*child);
  }

  m_container->add (*widget);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
