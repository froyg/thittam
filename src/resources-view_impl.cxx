/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resources-view_impl.h"

NAMESPACE__THITTAM__START

ResourcesViewImpl::ResourcesViewImpl (
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

  this->init_toolbar (builder);
  this->init_menu (builder);
  this->init_tree (builder);

  this->enable_add_resource (false);
  this->enable_add_group (true);
}

void ResourcesViewImpl::init_toolbar (Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget ("tb-add-resource", m_btn_add_resource);
  builder->get_widget ("tb-add-group", m_btn_add_group);

  m_btn_add_resource->signal_clicked ().connect (
    sigc::mem_fun (*this, &ResourcesViewImpl::cb_on_add_resource_clicked));
  m_btn_add_group->signal_clicked ().connect (
    sigc::mem_fun (*this, &ResourcesViewImpl::cb_on_add_group_clicked));
}


void ResourcesViewImpl::init_menu (Glib::RefPtr<Gtk::Builder> builder)
{
  m_action_group = Gio::SimpleActionGroup::create ();

  m_action_add_resource = m_action_group->add_action (
    "add",
    sigc::mem_fun (*this, &ResourcesViewImpl::cb_on_add_resource_clicked));
  m_action_add_group = m_action_group->add_action (
    "add-group",
    sigc::mem_fun (*this, &ResourcesViewImpl::cb_on_add_group_clicked));

  m_top_widget->insert_action_group ("resource", m_action_group);

  builder->get_widget ("resource-popup", m_menu);
  builder->get_widget ("menu-add-resource", m_menu_add_resource);
  builder->get_widget ("menu-add-resource-group", m_menu_add_group);
}


void ResourcesViewImpl::init_tree (Glib::RefPtr<Gtk::Builder> builder)
{
  m_tree_store = Gtk::TreeStore::create (m_cols);
  m_tree_view.set_model (m_tree_store);

  m_tree_view.append_column ("ID", m_cols.id);
  m_tree_view.append_column_editable ("Name", m_cols.name);
  m_tree_view.append_column_editable ("Cost", m_cols.cost);

  m_tree_store->signal_row_changed ().connect (
    sigc::mem_fun (*this, &ResourcesViewImpl::cb_on_row_changed));

  m_tree_selection = m_tree_view.get_selection ();
  m_tree_selection->signal_changed ().connect
    (sigc::mem_fun (*this, &ResourcesViewImpl::cb_on_row_selected));

  Gtk::ScrolledWindow * tree_container = nullptr;
  builder->get_widget ("tree-container", tree_container);
  tree_container->add (m_tree_view);

  Gtk::Box* top_box = dynamic_cast<Gtk::Box*> (m_top_widget);
  top_box->show_all_children ();
}

void ResourcesViewImpl::cb_on_add_resource_clicked (void)
{
}

void ResourcesViewImpl::cb_on_add_group_clicked(void)
{
  m_handler->view_add_group_clicked ();
}

void ResourcesViewImpl::cb_on_row_selected (void)
{
}

void ResourcesViewImpl::cb_on_row_changed (
  const Gtk::TreeModel::Path& path,
  const Gtk::TreeModel::iterator& iter)
{
}

void ResourcesViewImpl::enable_add_resource (bool enable)
{
  m_action_add_resource->set_enabled (enable);
  m_menu_add_resource->set_sensitive (enable);
  m_btn_add_resource->set_sensitive (enable);
}

void ResourcesViewImpl::enable_add_group (bool enable)
{
  m_action_add_group->set_enabled (enable);
  m_menu_add_group->set_sensitive (enable);
  m_btn_add_group->set_sensitive (enable);
}

void ResourcesViewImpl::enable_delete (bool enable)
{
}

void ResourcesViewImpl::add_resource ()
{
}

void ResourcesViewImpl::add_group (const std::string &id,
                                   const std::string &name)
{
  auto row = *m_tree_store->append ();
  row[m_cols.id] = id;
  row[m_cols.name] = name;
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
