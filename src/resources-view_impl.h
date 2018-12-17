/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__0da5375c_5a93_11e8_a301_448500dfb04c
#define HIPRO__0da5375c_5a93_11e8_a301_448500dfb04c

#include <gtkmm.h>

#include "resources-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourcesViewImpl : public ResourcesView
{
public:
  ResourcesViewImpl (
    hipro::log::Logger* logger, Glib::RefPtr<Gtk::Builder> builder);

  /*--- ResourcesView interface ---*/
  Gtk::Widget* widget (void)
  {
    return m_top_widget;
  }

  void set_handler (ResourcesViewCallbacks* handler)
  {
    m_handler = handler;
  }

  void init_toolbar (Glib::RefPtr<Gtk::Builder> builder);
  void init_menu (Glib::RefPtr<Gtk::Builder> builder);
  void init_tree (Glib::RefPtr<Gtk::Builder> builder);

  void enable_add_resource (bool enable);
  void enable_add_group (bool enable);
  void enable_delete (bool enable);

  void add_resource (void);
  void add_group (const std::string &id, const std::string &name);

private:
  class Columns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    Columns ()
    {
      add (id);
      add (name);
      add (cost);
    }

    Gtk::TreeModelColumn<Glib::ustring> id;
    Gtk::TreeModelColumn<Glib::ustring> name;
    Gtk::TreeModelColumn<float> cost;
  } m_cols;

  Gtk::TreeView m_tree_view;
  Glib::RefPtr<Gtk::TreeStore> m_tree_store;
  Glib::RefPtr<Gtk::TreeSelection> m_tree_selection;

  Gtk::ToolButton * m_btn_add_resource = nullptr;
  Gtk::ToolButton * m_btn_add_group = nullptr;

  Glib::RefPtr<Gio::SimpleActionGroup> m_action_group;
  Glib::RefPtr<Gio::SimpleAction> m_action_add_resource;
  Glib::RefPtr<Gio::SimpleAction> m_action_add_group;

  Gtk::Menu* m_menu = nullptr;
  Gtk::MenuItem* m_menu_add_resource = nullptr;
  Gtk::MenuItem* m_menu_add_group = nullptr;

  void cb_on_add_resource_clicked (void);
  void cb_on_add_group_clicked(void);
  void cb_on_row_selected (void);
  void cb_on_row_changed (
    const Gtk::TreeModel::Path&,
    const Gtk::TreeModel::iterator&);

  hipro::log::Logger* logger = nullptr;

  Gtk::Widget* m_top_widget = nullptr;
  ResourcesViewCallbacks* m_handler = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__0da5375c_5a93_11e8_a301_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
