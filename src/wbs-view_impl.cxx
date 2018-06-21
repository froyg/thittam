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
  : logger (logger),
    m_builder (builder)
{
  builder->get_widget ("top-widget", m_top_widget);
  auto parent = m_top_widget->get_parent ();
  if (parent)
  {
    parent->remove (*m_top_widget);
  }

  Gtk::ToolButton* btn;
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

  builder->get_widget ("context-menu", m_menu);
  builder->get_widget ("menu-add-child", m_menu_add_child);
  builder->get_widget ("menu-add-sibling", m_menu_add_sibling);

  builder->get_widget ("tree-view", m_tree_view);

  m_tree_view->signal_button_press_event ().connect_notify
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_button_pressed));
  m_tree_view->signal_row_activated ().connect
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_row_activated));

  auto crt1 = Glib::RefPtr<Gtk::CellRendererText>::cast_static (
    builder->get_object ("tv-cell-title"));
  crt1->signal_edited ().connect
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_title_edit));

  auto crt2 = Glib::RefPtr<Gtk::CellRendererText>::cast_static (
    builder->get_object ("tv-cell-effort"));
  crt2->signal_edited ().connect
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_effort_edit));

  m_tree_selection = m_tree_view->get_selection ();
  m_tree_selection->signal_changed ().connect
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_row_selected));
}

void
WBSViewImpl::cb_on_row_selected (void)
{
  auto it = m_tree_selection->get_selected ();
  std::string chosen_id;
  it->get_value (0, chosen_id);
  m_handler->view_node_selected (chosen_id);
}

void
WBSViewImpl::cb_on_button_pressed (GdkEventButton * event)
{
  if (((int)event->type == (int)Gdk::BUTTON_PRESS) && (event->button == 3))
    {
      Gtk::TreeModel::Path path;
      if (m_tree_view->get_path_at_pos (event->x, event->y, path))
        {
          m_tree_view->grab_focus ();
          m_tree_view->set_cursor (path);
          m_menu->popup (event->button, event->time);
        }
    }
}

void
WBSViewImpl::cb_on_row_activated (
  const Gtk::TreeModel::Path & path,
  Gtk::TreeViewColumn * column)
{
  auto it = m_tree_selection->get_selected ();
  std::string chosen_id;
  it->get_value (0, chosen_id);

  m_handler->view_node_activated (chosen_id);
}

void
WBSViewImpl::cb_on_add_child_clicked (void)
{
  m_handler->view_add_child_clicked ();
}

void
WBSViewImpl::cb_on_add_sibling_clicked (void)
{
  m_handler->view_add_sibling_clicked ();
}

void
WBSViewImpl::cb_on_cut_clicked (void)
{
  m_handler->view_cut_clicked ();
}

void
WBSViewImpl::cb_on_copy_clicked (void)
{
  m_handler->view_copy_clicked ();
}

void
WBSViewImpl::cb_on_paste_clicked (void)
{
  m_handler->view_paste_clicked ();
}

void
WBSViewImpl::cb_on_delete_clicked (void)
{
  m_handler->view_delete_clicked ();
}

void
WBSViewImpl::cb_on_indent_clicked (void)
{
  m_handler->view_indent_clicked ();
}

void
WBSViewImpl::cb_on_unindent_clicked (void)
{
  m_handler->view_unindent_clicked ();
}

void
WBSViewImpl::cb_on_up_clicked (void)
{
  m_handler->view_up_clicked ();
}

void
WBSViewImpl::cb_on_down_clicked (void)
{
  m_handler->view_down_clicked ();
}

void
WBSViewImpl::cb_on_title_edit (
  const Glib::ustring & path,
  const Glib::ustring & new_text)
{
  m_handler->view_title_changed (new_text);
}

void
WBSViewImpl::cb_on_effort_edit (
  const Glib::ustring & path,
  const Glib::ustring & new_text)
{
  m_handler->view_effort_changed (new_text);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
