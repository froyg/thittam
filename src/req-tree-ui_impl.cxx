/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <gtkmm.h>

#include "req-tree-ui_impl.h"

ReqTreeUIImpl::ReqTreeUIImpl (HLogPtr logger,
                              Glib::RefPtr<Gtk::Builder> builder) :
  m_logger (logger)
{
  Gtk::TreeView * tv;
  builder->get_widget ("req-tree-view", tv);
  m_tree_view = std::unique_ptr<Gtk::TreeView> (tv);

  /* signals related to TreeView */
  m_tree_view->signal_button_press_event ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_button_pressed));
  m_tree_view->signal_row_activated ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_row_activated));
  m_tree_view->signal_cursor_changed ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_cursor_changed));

  /* signals related to TreeSelection */
  m_tree_selection = m_tree_view->get_selection ();
  m_tree_selection->signal_changed ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_row_selected));


  /* Get menu items and listen for their signals */
  builder->get_widget ("menu-node", m_menu_node);

  builder->get_widget ("menu-node-add-child", m_menu_node_add_child);
  m_menu_node_add_child->signal_activate ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_add_child));

  builder->get_widget ("menu-node-add-sibling", m_menu_node_add_sibling);
  m_menu_node_add_sibling->signal_activate ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_add_sibling));

  builder->get_widget ("menu-node-cut", m_menu_node_cut);
  m_menu_node_cut->signal_activate ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_cut));

  builder->get_widget ("menu-node-copy", m_menu_node_copy);
  m_menu_node_copy->signal_activate ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_copy));

  builder->get_widget ("menu-node-paste", m_menu_node_paste);
  m_menu_node_paste->signal_activate ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_paste));

  builder->get_widget ("menu-node-delete", m_menu_node_delete);
  m_menu_node_delete->signal_activate ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_delete));

  /* Get toolbar items and listen for their signals */
  builder->get_widget ("tb-cut", m_tb_node_cut);
  m_tb_node_cut->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_cut));

  builder->get_widget ("tb-copy", m_tb_node_copy);
  m_tb_node_copy->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_copy));

  builder->get_widget ("tb-paste", m_tb_node_paste);
  m_tb_node_paste->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_paste));

  builder->get_widget ("tb-delete", m_tb_node_delete);
  m_tb_node_delete->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_delete));

  builder->get_widget ("tb-indent", m_tb_node_indent);
  m_tb_node_indent->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_indent));

  builder->get_widget ("tb-unindent", m_tb_node_unindent);
  m_tb_node_unindent->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_unindent));

  builder->get_widget ("tb-up", m_tb_node_up);
  m_tb_node_up->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_move_up));

  builder->get_widget ("tb-down", m_tb_node_down);
  m_tb_node_up->signal_clicked ().connect
    (sigc::mem_fun (this, &ReqTreeUIImpl::cb_on_move_down));

  /* Set the initial menu state */
  m_menu_node_add_child->set_sensitive (true);
  m_menu_node_add_sibling->set_sensitive (false);
  m_menu_node_cut->set_sensitive (false);
  m_menu_node_copy->set_sensitive (false);
  m_menu_node_paste->set_sensitive (false);
  m_menu_node_delete->set_sensitive (false);
  m_tb_node_cut->set_sensitive (false);
  m_tb_node_copy->set_sensitive (false);
  m_tb_node_paste->set_sensitive (false);
  m_tb_node_delete->set_sensitive (false);
  m_tb_node_indent->set_sensitive (false);
  m_tb_node_unindent->set_sensitive (false);
  m_tb_node_up->set_sensitive (false);
  m_tb_node_down->set_sensitive (false);


}

void
ReqTreeUIImpl::cb_on_row_selected (void)
{
  Log_D1 << "cb_on_row_selected: Not yet implemented";
}

bool
ReqTreeUIImpl::cb_on_button_pressed (GdkEventButton * event)
{
  Log_D1 << "cb_on_button_pressed: Not yet implemented";
  return false;
}

void
ReqTreeUIImpl::cb_on_row_activated (const Gtk::TreeModel::Path & path,
                                    Gtk::TreeViewColumn * column)
{
  Log_D1 << "cb_on_row_activated: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_cursor_changed (void)
{
  Log_D1 << "cb_on_cursor_changed: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_add_child (void)
{
  Log_D1 << "cb_on_add_child: Not yet implemented";
  // auto it = m_tree_selection->get_selected ();
  // if (it)
  //   {
  //     auto req = get_req_from_iter (it);
  //   }
}

void
ReqTreeUIImpl::cb_on_add_sibling (void)
{
  Log_D1 << "cb_on_add_sibling: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_cut (void)
{
  Log_D1 << "cb_on_cut: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_copy (void)
{
  Log_D1 << "cb_on_copy: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_delete (void)
{
  Log_D1 << "cb_on_delete: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_paste (void)
{
  Log_D1 << "cb_on_paste: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_indent (void)
{
  Log_D1 << "cb_on_indent: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_unindent (void)
{
  Log_D1 << "cb_on_unindent: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_move_up (void)
{
  Log_D1 << "cb_on_move_up: Not yet implemented";
}

void
ReqTreeUIImpl::cb_on_move_down (void)
{
  Log_D1 << "cb_on_move_down: Not yet implemented";
}

Requirement::ptr_t
ReqTreeUIImpl::get_req_from_iter (Gtk::TreeModel::iterator it)
{
  ASSERT ((it), "Given iterator is invalid");
  std::string reqid;
  const Gtk::TreeModel::Row & row = *it;
  row.get_value (0, reqid);
  return m_req_tree->get (reqid);
}

void
ReqTreeUIImpl::enable_node_operation (bool state)
{
  m_menu_node_add_sibling->set_sensitive (state);
  m_menu_node_cut->set_sensitive (state);
  m_menu_node_copy->set_sensitive (state);
  m_menu_node_paste->set_sensitive (state);
  m_menu_node_delete->set_sensitive (state);
  m_tb_node_cut->set_sensitive (state);
  m_tb_node_copy->set_sensitive (state);
  m_tb_node_paste->set_sensitive (state);
  m_tb_node_delete->set_sensitive (state);
}

void
ReqTreeUIImpl::enable_node_manipulation (bool state)
{
  m_tb_node_indent->set_sensitive (state);
  m_tb_node_unindent->set_sensitive (state);
  m_tb_node_up->set_sensitive (state);
  m_tb_node_down->set_sensitive (state);
}

void
ReqTreeUIImpl::display (Requirement::ptr_t req)
{
  m_lbl_node_info_reqid->set_label (req->id ());
  m_lbl_node_info_title->set_label (req->title ());
  m_lbl_node_info_description->set_label (req->description ());
}
/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
