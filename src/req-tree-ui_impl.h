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
#include "req-tree-ui.h"

class ReqTreeUIImpl : public ReqTreeUI
{
public:
  typedef std::shared_ptr<ReqTreeUIImpl> ptr_t;

public:
  /* -------- ctor/dtor ------------ */
  static ptr_t create (HLogPtr logger,
                       Glib::RefPtr<Gtk::Builder> builder)
  {
    ptr_t object (new ReqTreeUIImpl (logger, builder));
    return object;
  }

  ReqTreeUIImpl (HLogPtr logger, Glib::RefPtr<Gtk::Builder> builder);
  ~ReqTreeUIImpl () {}

  /* -------- methods needed by interface -------- */
  void load (ReqTree::ptr_t req_tree)
  {
    Log_D1 << "load: Not yet implemented";
  }

private:
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

private:
  HLogPtr m_logger;
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
