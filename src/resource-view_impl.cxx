/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <iomanip>

#include "resource-view_impl.h"

NAMESPACE__THITTAM__START

ResourceViewImpl::ResourceViewImpl (
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder,
  Gtk::Window* parent)
  : logger (logger),
    m_parent (parent)
{
  builder->get_widget ("top-widget", m_top_window);
  auto old_parent = m_top_window->get_parent ();
  if (old_parent)
  {
    old_parent->remove (*m_top_window);
  }

  builder->get_widget ("ent-short-name", m_ent_short_name);
  builder->get_widget ("ent-long-name", m_ent_long_name);
  builder->get_widget ("ent-cost", m_ent_cost);
  builder->get_widget ("ent-description", m_ent_description);

  Gtk::Button* btn = nullptr;
  builder->get_widget ("btn-save", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &ResourceViewImpl::cb_on_save_clicked));

  builder->get_widget ("btn-cancel", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &ResourceViewImpl::cb_on_cancel_clicked));
}

void
ResourceViewImpl::show (void)
{
  m_top_window->set_transient_for (*m_parent);
  m_top_window->set_modal (true);
  m_top_window->show ();
}

void
ResourceViewImpl::hide (void)
{
  m_top_window->hide ();
  m_top_window->set_modal (false);
  m_top_window->unset_transient_for ();
}

void
ResourceViewImpl::set_short_name (const std::string& short_name)
{
  m_ent_short_name->set_text (short_name);
}

void
ResourceViewImpl::set_long_name (const std::string& long_name)
{
  m_ent_long_name->set_text (long_name);
}

void
ResourceViewImpl::set_cost (double cost)
{
  std::ostringstream os;
  os << std::setprecision (2) << cost;
  m_ent_cost->set_text (os.str ());
}

void
ResourceViewImpl::set_description (const std::string& description)
{
  m_ent_description->set_text (description);
}

const std::string&
ResourceViewImpl::short_name (void) const
{
  m_short_name = m_ent_short_name->get_text ();
  return m_short_name.raw ();
}

const std::string&
ResourceViewImpl::long_name (void) const
{
  m_long_name = m_ent_long_name->get_text ();
  return m_long_name.raw ();
}

double
ResourceViewImpl::cost (void) const
{
  m_cost = m_ent_cost->get_text ();
  double cost;
  std::istringstream is (m_cost.raw ());
  is >> std::setprecision (2) >> cost;
  return cost;
}

const std::string&
ResourceViewImpl::description (void) const
{
  m_description = m_ent_description->get_text ();
  return m_description.raw ();
}

void
ResourceViewImpl::cb_on_save_clicked (void)
{
  m_handler->view_save_pressed ();
}

void
ResourceViewImpl::cb_on_cancel_clicked (void)
{
  m_handler->view_cancel_pressed ();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
