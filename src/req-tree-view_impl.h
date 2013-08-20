/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__36cedf5e_fe89_11e2_9892_68a3c42125fd
#define HIPRO_THITTAM__36cedf5e_fe89_11e2_9892_68a3c42125fd

#include <memory>

#include <gtkmm.h>

#include <boost/signals2.hpp>

#include "common.h"
#include "req-tree.h"
#include "requirement.h"
#include "req-tree-view.h"
#include "req-view.h"

class ReqTreeViewImpl : public ReqTreeView
{
public:
  /* -------- ctor/dtor ------------ */
  ReqTreeViewImpl (HLogPtr logger, Glib::RefPtr<Gtk::Builder> builder);
  ~ReqTreeViewImpl () {}

  /* -------- methods needed by interface -------- */
  void load (std::shared_ptr<ReqTree> req_tree)
  {
    Log_D1 << "load: Not yet implemented";
    m_req_tree = req_tree;
  }

private:
  /* Gtk signal callback handlers */
  void cb_on_row_selected (void);
  bool cb_on_button_pressed (GdkEventButton * event);
  void cb_on_row_activated (const Gtk::TreeModel::Path & path,
                            Gtk::TreeViewColumn * column);
  void cb_on_cursor_changed (void);
  void cb_on_add_child (void);
  void cb_on_add_sibling (void);
  void cb_on_cut (void);
  void cb_on_copy (void);
  void cb_on_paste (void);
  void cb_on_delete (void);
  void cb_on_indent (void);
  void cb_on_unindent (void);
  void cb_on_move_up (void);
  void cb_on_move_down (void);

  /* Other convenience methods */
  std::shared_ptr<Requirement> get_req_from_iter (Gtk::TreeModel::iterator it);
  void enable_node_operation (bool state);
  void enable_node_manipulation (std::shared_ptr<Requirement> req);
  void display (std::shared_ptr<Requirement> req);
  std::shared_ptr<Requirement> get_new (void);
  void load_ui_children (std::shared_ptr<Requirement> parent,
                         Gtk::TreeModel::iterator parent_iter);

private:
  HLogPtr m_logger;
  std::shared_ptr<ReqTree> m_req_tree;
  std::shared_ptr<ReqView> m_req_view;
  std::shared_ptr<Requirement> m_clipboard_req;
  std::shared_ptr<RequirementFactory> m_req_factory;
  bool m_clipboard_duplicate;
  std::unique_ptr<Gtk::TreeView> m_tree_view;
  Glib::RefPtr<Gtk::TreeStore> m_tree_store;
  Glib::RefPtr<Gtk::TreeSelection> m_tree_selection;
  Gtk::Menu * m_menu_node;
  Gtk::MenuItem * m_menu_node_add_child;
  Gtk::MenuItem * m_menu_node_add_sibling;
  Gtk::MenuItem * m_menu_node_cut;
  Gtk::MenuItem * m_menu_node_copy;
  Gtk::MenuItem * m_menu_node_paste;
  Gtk::MenuItem * m_menu_node_delete;
  Gtk::ToolButton * m_tb_node_cut;
  Gtk::ToolButton * m_tb_node_copy;
  Gtk::ToolButton * m_tb_node_paste;
  Gtk::ToolButton * m_tb_node_delete;
  Gtk::ToolButton * m_tb_node_indent;
  Gtk::ToolButton * m_tb_node_unindent;
  Gtk::ToolButton * m_tb_node_up;
  Gtk::ToolButton * m_tb_node_down;
  Gtk::Label * m_lbl_node_info_reqid;
  Gtk::Label * m_lbl_node_info_title;
  Gtk::Label * m_lbl_node_info_description;

};

#endif // HIPRO_THITTAM__36cedf5e_fe89_11e2_9892_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
