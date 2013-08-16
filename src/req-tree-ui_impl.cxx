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
#include "req-form-ui_impl.h"

ReqTreeUIImpl::ReqTreeUIImpl (HLogPtr logger,
                              Glib::RefPtr<Gtk::Builder> builder) :
  m_logger (logger),
  m_clipboard_duplicate (false)
{
  /* create the requirement form UI in order to be used later */
  m_req_form_ui = ReqFormUIImpl::create (logger);

  Gtk::TreeView * tv;
  builder->get_widget ("req-tree-view", tv);
  m_tree_view = std::unique_ptr<Gtk::TreeView> (tv);

  m_tree_store = Glib::RefPtr<Gtk::TreeStore>::cast_static
    (builder->get_object ("req-tree-store"));

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
  auto it = m_tree_selection->get_selected ();
  if (!it)
    {
      enable_node_operation (false);
      return;
    }
  enable_node_operation (true);
  auto req = get_req_from_iter (it);
  enable_node_manipulation (req);
}

bool
ReqTreeUIImpl::cb_on_button_pressed (GdkEventButton * event)
{
  if (((int)event->type == (int)Gdk::BUTTON_PRESS) && (event->button == 3))
    {
      Gtk::TreeModel::Path path;
      if (m_tree_view->get_path_at_pos (event->x, event->y, path))
        {
          m_tree_view->grab_focus ();
          m_tree_view->set_cursor (path);
          m_menu_node->popup (event->button, event->time);
          return true;
        }
    }
  return false;
}

void
ReqTreeUIImpl::cb_on_row_activated (const Gtk::TreeModel::Path & path,
                                    Gtk::TreeViewColumn * column)
{
  auto it = m_tree_selection->get_selected ();
  auto req = get_req_from_iter (it);
  if (m_req_form_ui->show (req) != Gtk::RESPONSE_OK)
    {
      m_req_form_ui->hide ();
      return;
    }
  req->set_title (m_req_form_ui->title ());
  req->set_description (m_req_form_ui->description ());
  display (req);
  Gtk::TreeModel::Row row = *it;
  row.set_value(1, req->title ());
  m_req_tree->set_dirty ();
  m_req_form_ui->hide ();
}

void
ReqTreeUIImpl::cb_on_cursor_changed (void)
{
  auto it = m_tree_selection->get_selected ();
  if (!it)
    {
      return;
    }
  auto req = get_req_from_iter (it);
  display (req);
}

void
ReqTreeUIImpl::cb_on_add_child (void)
{
  ASSERT ((m_req_tree), "Requirement tree model not yet set");
  auto new_req = get_new ();
  if (!new_req)
    {
      return;
    }
  std::shared_ptr<Requirement> sel_req = nullptr;
  auto it = m_tree_selection->get_selected ();
  Gtk::TreeModel::Row row;
  if (it)
    {
      row = *(m_tree_store->append (it->children ()));
      sel_req = get_req_from_iter (it);
      auto path = m_tree_store->get_path (it);
      m_tree_view->expand_row (path, false);
      enable_node_manipulation (sel_req);
    }
  else
    {
      row = *(m_tree_store->append ());
    }
  row.set_value (0, m_req_tree->add_child (sel_req, new_req, false));
  row.set_value (1, new_req->title ());
}

void
ReqTreeUIImpl::cb_on_add_sibling (void)
{
  ASSERT ((m_req_tree), "Requirement tree model not yet set");
  auto new_req = get_new ();
  if (!new_req)
    {
      return;
    }
  std::shared_ptr<Requirement> sel_req = nullptr;
  auto it = m_tree_selection->get_selected ();
  Gtk::TreeModel::Row row;
  if (it)
    {
      row = *(m_tree_store->insert_after (it));
      sel_req = get_req_from_iter (it);
      enable_node_manipulation (sel_req);
    }
  else
    {
      row = *(m_tree_store->append ());
    }
  row.set_value (0, m_req_tree->add_sibling (sel_req, new_req, false));
  row.set_value (1, new_req->title ());
}

void
ReqTreeUIImpl::cb_on_cut (void)
{
  auto it = m_tree_selection->get_selected ();
  if (it)
    {
      m_clipboard_req = get_req_from_iter (it);
      m_req_tree->detach (m_clipboard_req);
      m_clipboard_duplicate = false;
      m_tree_store->erase (it);
    }
}

void
ReqTreeUIImpl::cb_on_copy (void)
{
  auto it = m_tree_selection->get_selected ();
  if (it)
    {
      m_clipboard_req = get_req_from_iter (it);
      m_clipboard_duplicate = true;
    }
}

void
ReqTreeUIImpl::cb_on_delete (void)
{
  auto it = m_tree_selection->get_selected ();
  if (it)
    {
      m_req_tree->detach (get_req_from_iter (it));
      m_tree_store->erase (it);
    }
}

void
ReqTreeUIImpl::cb_on_paste (void)
{
  if (!m_clipboard_req)
    {
      return;
    }
  auto it = m_tree_selection->get_selected ();
  auto parent_req = get_req_from_iter (it);
  m_req_tree->add_child (parent_req, m_clipboard_req, m_clipboard_duplicate);
  auto new_it = m_tree_store->append (it->children ());
  Gtk::TreeModel::Row row = *new_it;
  row.set_value (0, m_clipboard_req->id ());
  row.set_value (1, m_clipboard_req->title ());
  load_ui_children (m_clipboard_req, new_it);
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
  auto it = m_tree_selection->get_selected ();
  auto req = get_req_from_iter (it);
  ASSERT ((!m_req_tree->is_first_child (req)), "Logic error: Can't move up");
  /* Update the req-tree backend */
  m_req_tree->up_child (req);
  /* Update the UI */
  it--; /* Get the previous iter and do insert operation before it */
  auto new_it =  m_tree_store->insert (it);
  Gtk::TreeModel::Row row = *new_it;
  row.set_value (0, req->id ());
  row.set_value (1, req->title ());
  /* Load the sub-nodes of it, if any */
  load_ui_children (req, new_it);
  /* As the iterator have been changed get the selected iter again and
     remove it from the tree-store */
  it = m_tree_selection->get_selected ();
  m_tree_store->erase (it);
  /* Set the selection to the newly added node */
  m_tree_selection->select (new_it);
}

void
ReqTreeUIImpl::cb_on_move_down (void)
{
  auto it = m_tree_selection->get_selected ();
  auto req = get_req_from_iter (it);
  ASSERT ((!m_req_tree->is_last_child (req)), "Logic error: Can't move down");
  /* Update the req-tree backend */
  m_req_tree->down_child (req);
  /* Update the UI */
  it++;
  auto new_it = m_tree_store->insert_after (it);
  Gtk::TreeModel::Row row = *new_it;
  row.set_value (0, req->id ());
  row.set_value (1, req->title ());
  /* Load the sub-nodes of it, if any */
  load_ui_children (req, new_it);
  /* As the iterator have been changed get the selected iter again and
     remove it from the tree-store */
  it = m_tree_selection->get_selected ();
  m_tree_store->erase (it);
  /* Set the selection to the newly added node */
  m_tree_selection->select (new_it);
}

std::shared_ptr<Requirement>
ReqTreeUIImpl::get_req_from_iter (Gtk::TreeModel::iterator it)
{
  ASSERT ((m_req_tree), "Requirement tree model not yet set");
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
ReqTreeUIImpl::enable_node_manipulation (std::shared_ptr<Requirement> req)
{
  ASSERT ((m_req_tree), "Requirement tree model not yet set");
  ASSERT ((req), "Invalid Requirement");
  //m_tb_node_indent->set_sensitive (!m_req_tree->is_bottom_level (req));
  m_tb_node_unindent->set_sensitive (!m_req_tree->is_top_level (req));
  m_tb_node_up->set_sensitive (!m_req_tree->is_first_child (req));
  m_tb_node_down->set_sensitive (!m_req_tree->is_last_child (req));
}

void
ReqTreeUIImpl::display (std::shared_ptr<Requirement> req)
{
  ASSERT ((req), "Invalid Requirement");
  m_lbl_node_info_reqid->set_label (req->id ());
  m_lbl_node_info_title->set_label (req->title ());
  m_lbl_node_info_description->set_label (req->description ());
}

std::shared_ptr<Requirement>
ReqTreeUIImpl::get_new (void)
{
  ASSERT ((m_req_form_ui), "Invalid requirement form UI");
  if (m_req_form_ui->show () != Gtk::RESPONSE_OK)
    {
      m_req_form_ui->hide ();
      return nullptr;
    }
  /* Create the requirement from the form ui entered fields and add it
     to the local treestore */
  m_req_form_ui->hide ();
  return nullptr; /* Has to be fixed */
}

void
ReqTreeUIImpl::load_ui_children (std::shared_ptr<Requirement> parent,
                                 Gtk::TreeModel::iterator parent_iter)
{
  auto end = parent->children_cend ();
  for (auto it = parent->children_cbegin (); it != end; ++it)
    {
      auto tree_iter = m_tree_store->append (parent_iter->children ());
      Gtk::TreeModel::Row row = *tree_iter;
      row.set_value(0, (*it)->id ());
      row.set_value(1, (*it)->title ());
      load_ui_children (*it, tree_iter);
    }
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
