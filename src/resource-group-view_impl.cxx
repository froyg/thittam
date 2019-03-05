/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resource-group-view_impl.h"

NAMESPACE__THITTAM__START

ResourceGroupViewImpl::ResourceGroupViewImpl(
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder,
  Gtk::Window* parent)
  : logger(logger),
    m_parent(parent)
{
  builder->get_widget("top-widget", m_top_window);
  auto old_parent = m_top_window->get_parent();
  if (old_parent) {
    old_parent->remove(*m_top_window);
  }

  builder->get_widget("ent-name", m_ent_name);
  builder->get_widget("ent-description", m_ent_description);

  Gtk::Button* btn = nullptr;
  builder->get_widget("btn-save", btn);
  btn->signal_clicked().connect(
    sigc::mem_fun(*this, &ResourceGroupViewImpl::cb_on_save_clicked));

  builder->get_widget("btn-cancel", btn);
  btn->signal_clicked().connect(
    sigc::mem_fun(*this, &ResourceGroupViewImpl::cb_on_cancel_clicked));
}

void
ResourceGroupViewImpl::show(void)
{
  m_top_window->set_transient_for(*m_parent);
  m_top_window->set_modal(true);
  m_top_window->show();
}

void
ResourceGroupViewImpl::hide(void)
{
  m_top_window->hide();
  m_top_window->set_modal(false);
  m_top_window->unset_transient_for();
}

void
ResourceGroupViewImpl::set_name(const std::string& name)
{
  m_ent_name->set_text(name);
}

void
ResourceGroupViewImpl::set_description(const std::string& description)
{
  m_ent_description->set_text(description);
}

const std::string&
ResourceGroupViewImpl::name(void) const
{
  m_name = m_ent_name->get_text();
  return m_name.raw();
}

const std::string&
ResourceGroupViewImpl::description(void) const
{
  m_description = m_ent_description->get_text();
  return m_description.raw();
}

void
ResourceGroupViewImpl::cb_on_save_clicked(void)
{
  m_handler->view_save_pressed();
}

void
ResourceGroupViewImpl::cb_on_cancel_clicked(void)
{
  m_handler->view_cancel_pressed();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
