/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "wbs-view_impl.h"

NAMESPACE__THITTAM__START

WBSViewImpl::WBSViewImpl (
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

  Gtk::ToolButton* btn;
  builder->get_widget ("tb-add", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_add_clicked));

  builder->get_widget ("tb-cut", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_cut_clicked));

  builder->get_widget ("tb-copy", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_copy_clicked));

  builder->get_widget ("tb-paste", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_paste_clicked));

  builder->get_widget ("tb-delete", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_delete_clicked));

  builder->get_widget ("tb-indent", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_indent_clicked));

  builder->get_widget ("tb-unindent", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_unindent_clicked));

  builder->get_widget ("tb-up", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_up_clicked));

  builder->get_widget ("tb-down", btn);
  btn->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_down_clicked));
}

void
WBSViewImpl::cb_on_add_clicked (void)
{

}

void
WBSViewImpl::cb_on_cut_clicked (void)
{

}

void
WBSViewImpl::cb_on_copy_clicked (void)
{

}

void
WBSViewImpl::cb_on_paste_clicked (void)
{

}

void
WBSViewImpl::cb_on_delete_clicked (void)
{

}

void
WBSViewImpl::cb_on_indent_clicked (void)
{

}

void
WBSViewImpl::cb_on_unindent_clicked (void)
{

}

void
WBSViewImpl::cb_on_up_clicked (void)
{

}

void
WBSViewImpl::cb_on_down_clicked (void)
{

}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
