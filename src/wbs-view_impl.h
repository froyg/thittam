/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__ea1bea38_59c5_11e8_892c_448500dfb04c
#define HIPRO__ea1bea38_59c5_11e8_892c_448500dfb04c

#include <gtkmm.h>

#include "wbs-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class WBSViewImpl : public WBSView
{
public:
  WBSViewImpl (hipro::log::Logger* logger, Glib::RefPtr<Gtk::Builder> builder);

  /*--- WBSView interface ---*/
  Gtk::Widget* widget (void)
  {
    return m_top_widget;
  }

  void set_handler (WBSViewCallbacks* handler)
  {
    m_handler = handler;
  }

  void enable_add_child (bool enable);
  void enable_add_sibling (bool enable);
  void enable_indent_task (bool enable);
  void enable_unindent_task (bool enable);
  void enable_up (bool enable);
  void enable_down (bool enable);
  void enable_cut (bool enable);
  void enable_copy (bool enable);
  void enable_paste (bool enable);
  void enable_delete (bool enable);

  void add_child (const WBS::Path & path);
  void indent (const WBS::Path & path);
  void unindent (const WBS::Path & path);
  void renumber (void);

private:
  void cb_on_row_selected (void);
  void cb_on_button_pressed (GdkEventButton * event);
  void cb_on_row_activated (
    const Gtk::TreeModel::Path & path,
    Gtk::TreeViewColumn * column);
  void cb_on_add_child_clicked (void);
  void cb_on_add_sibling_clicked (void);
  void cb_on_cut_clicked (void);
  void cb_on_copy_clicked (void);
  void cb_on_paste_clicked (void);
  void cb_on_delete_clicked (void);
  void cb_on_indent_clicked (void);
  void cb_on_unindent_clicked (void);
  void cb_on_up_clicked (void);
  void cb_on_down_clicked (void);
  void cb_on_row_changed (
    const Gtk::TreeModel::Path& path,
    const Gtk::TreeModel::iterator& iter);

  void do_renumber (
    const Gtk::TreeRow * row, const std::string & parent_id, int index);

  // Copy task details from one row to another row. Arg 1 is source.
  void copy_task(
    const Gtk::TreeRow &source,
    const Gtk::TreeRow &destination);

  // Recursively copy whole sub-tree from source to destination
  void copy_sub_tasks(
    const Gtk::TreeRow &source,
    const Gtk::TreeRow &destination);

private:
  hipro::log::Logger* logger = nullptr;
  Glib::RefPtr<Gtk::Builder> m_builder;

  bool m_self_change = false;
  Gtk::Widget* m_top_widget = nullptr;
  WBSViewCallbacks* m_handler = nullptr;

  class Columns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    Columns ()
    {
      add (id);
      add (title);
      add (effort);
    }

    Gtk::TreeModelColumn<Glib::ustring> id;
    Gtk::TreeModelColumn<Glib::ustring> title;
    Gtk::TreeModelColumn<Glib::ustring> effort;
  };

  Gtk::TreeView m_tree_view;
  Glib::RefPtr<Gtk::TreeStore> m_tree_store;
  Glib::RefPtr<Gtk::TreeSelection> m_tree_selection;
  Columns m_cols;

  Gtk::ToolButton * m_btn_cut = nullptr;
  Gtk::ToolButton * m_btn_copy = nullptr;
  Gtk::ToolButton * m_btn_paste = nullptr;
  Gtk::ToolButton * m_btn_delete = nullptr;
  Gtk::ToolButton * m_btn_indent = nullptr;
  Gtk::ToolButton * m_btn_unindent = nullptr;
  Gtk::ToolButton * m_btn_up = nullptr;
  Gtk::ToolButton * m_btn_down = nullptr;

  Gtk::ScrolledWindow * m_tree_container = nullptr;

  Glib::RefPtr<Gio::SimpleActionGroup> m_action_group;
  Glib::RefPtr<Gio::SimpleAction> m_action_add_child;
  Glib::RefPtr<Gio::SimpleAction> m_action_add_sibling;
  Glib::RefPtr<Gio::SimpleAction> m_action_indent;
  Glib::RefPtr<Gio::SimpleAction> m_action_unindent;

  Gtk::Menu* m_menu = nullptr;
  Gtk::MenuItem* m_menu_add_child = nullptr;
  Gtk::MenuItem* m_menu_add_sibling = nullptr;
  Gtk::MenuItem* m_menu_indent = nullptr;
  Gtk::MenuItem* m_menu_unindent = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__ea1bea38_59c5_11e8_892c_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
