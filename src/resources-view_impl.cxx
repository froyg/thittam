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

ResourcesViewImpl::ResourcesViewImpl(
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder)
  : logger(logger)
{
  builder->get_widget("top-widget", m_top_widget);
  auto parent = m_top_widget->get_parent();
  if (parent) {
    parent->remove(*m_top_widget);
  }

  this->init_toolbar(builder);
  this->init_menu(builder);
  this->init_tree(builder);

  this->enable_add_resource(false);
  this->enable_add_group(true);
}

void
ResourcesViewImpl::init_toolbar(Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget ( "tb-add-resource", m_btn_add_resource );
  builder->get_widget ( "tb-add-group", m_btn_add_group );
  builder->get_widget ( "tb-delete", m_btn_delete );

  m_btn_add_resource->signal_clicked().connect (
    sigc::mem_fun ( *this, &ResourcesViewImpl::cb_on_add_resource_clicked ) );
  m_btn_add_group->signal_clicked().connect (
    sigc::mem_fun ( *this, &ResourcesViewImpl::cb_on_add_group_clicked ) );
  m_btn_delete->signal_clicked().connect (
    sigc::mem_fun ( *this, &ResourcesViewImpl::cb_on_delete_clicked ) );
}

void
ResourcesViewImpl::init_menu(Glib::RefPtr<Gtk::Builder> builder)
{
  m_action_group = Gio::SimpleActionGroup::create();

  m_action_add_resource = m_action_group->add_action(
      "add",
      sigc::mem_fun(*this, &ResourcesViewImpl::cb_on_add_resource_clicked));
  m_action_add_group = m_action_group->add_action(
      "add-group",
      sigc::mem_fun ( *this, &ResourcesViewImpl::cb_on_add_group_clicked ) );
  m_action_delete = m_action_group->add_action (
      "delete", sigc::mem_fun ( *this, &ResourcesViewImpl::cb_on_delete_clicked ) );

  m_top_widget->insert_action_group("resource", m_action_group);

  builder->get_widget ( "resource-popup", m_menu );
  builder->get_widget ( "menu-add-resource", m_menu_add_resource );
  builder->get_widget ( "menu-add-resource-group", m_menu_add_group );
  builder->get_widget ( "menu-delete", m_menu_delete );
}

void
ResourcesViewImpl::init_tree(Glib::RefPtr<Gtk::Builder> builder)
{
  m_tree_store = Gtk::TreeStore::create(m_cols);
  m_tree_view.set_model(m_tree_store);

  m_tree_view.get_column(
    m_tree_view.append_column("ID", m_cols.id) - 1
  )->set_visible(false);
  m_tree_view.append_column_editable("Name", m_cols.name);
  m_tree_view.append_column_editable("Cost", m_cols.cost);
  m_tree_view.append_column_editable("Description", m_cols.description);

  m_tree_store->signal_row_changed().connect(
    sigc::mem_fun(*this, &ResourcesViewImpl::cb_on_row_changed));

  m_tree_selection = m_tree_view.get_selection();
  m_tree_selection->set_mode(Gtk::SELECTION_MULTIPLE);
  m_tree_selection->signal_changed().connect
  (sigc::mem_fun(*this, &ResourcesViewImpl::cb_on_row_selected));

  Gtk::ScrolledWindow* tree_container = nullptr;
  builder->get_widget("tree-container", tree_container);
  tree_container->add(m_tree_view);

  Gtk::Box* top_box = dynamic_cast<Gtk::Box*>(m_top_widget);
  top_box->show_all_children();
}

void
ResourcesViewImpl::cb_on_add_resource_clicked(void)
{
  m_handler->view_add_resource_clicked();
}

void
ResourcesViewImpl::cb_on_add_group_clicked(void)
{
  m_handler->view_add_group_clicked();
}

void
ResourcesViewImpl::cb_on_delete_clicked ( void )
{
  m_handler->view_delete_clicked();
}

void
ResourcesViewImpl::cb_on_row_selected ( void )
{
  const auto& paths = m_tree_selection->get_selected_rows();
  m_handler->view_node_selected(paths);
}

void
ResourcesViewImpl::cb_on_row_changed(
  const Gtk::TreeModel::Path& path,
  const Gtk::TreeModel::iterator& iter)
{
  m_handler->view_node_changed(path, *iter);
}

void
ResourcesViewImpl::set_id(
  const Gtk::TreeRow& row,
  const std::string& id)
{
  row.set_value(m_cols.id, id);
}

void
ResourcesViewImpl::set_name(
  const Gtk::TreeRow& row,
  const std::string& name)
{
  row.set_value(m_cols.name, name);
}

void
ResourcesViewImpl::set_cost(
  const Gtk::TreeRow& row,
  const float cost)
{
  row.set_value(m_cols.cost, cost);
}

std::string
ResourcesViewImpl::get_id(const Gtk::TreeIter row)
{
  return row->get_value(m_cols.id);
}

std::string
ResourcesViewImpl::get_name(const Gtk::TreeIter row)
{
  return row->get_value(m_cols.name);
}

float
ResourcesViewImpl::get_cost(const Gtk::TreeIter row)
{
  return row->get_value(m_cols.cost);
}

const Gtk::TreeIter
ResourcesViewImpl::path_to_rowiter(const Gtk::TreePath& p)
{
  return m_tree_store->get_iter(p);
}

bool
ResourcesViewImpl::node_is_selected(const Gtk::TreeModel::Path& path)
{
  return m_tree_selection->is_selected(path);
}

bool
ResourcesViewImpl::is_group(const Gtk::TreeModel::Path& path)
{
  return path.size() == 1;
}

void
ResourcesViewImpl::enable_add_resource(bool enable)
{
  m_action_add_resource->set_enabled(enable);
  // m_menu_add_resource->set_sensitive (enable);
  m_btn_add_resource->set_sensitive(enable);
}

void
ResourcesViewImpl::enable_add_group(bool enable)
{
  m_action_add_group->set_enabled(enable);
  // m_menu_add_group->set_sensitive(enable);
  m_btn_add_group->set_sensitive(enable);
}

void
ResourcesViewImpl::enable_delete(bool enable)
{
  m_action_delete->set_enabled ( enable );
  // todo: gives segfault
  // m_menu_add_group->set_sensitive(enable);
  m_btn_add_group->set_sensitive ( enable );
}

void
ResourcesViewImpl::add_resource(
  const int group_index,
  const std::string& id,
  const std::string& name,
  const float cost,
  const std::string& description)
{
  Gtk::TreeModel::Path p;
  p.push_back(group_index);
  auto resource_group = *m_tree_store->get_iter(p);
  auto& resource = *m_tree_store->append(resource_group.children());
  resource.set_value(m_cols.id, id);
  resource.set_value(m_cols.name, name);
  resource.set_value(m_cols.cost, cost);
  resource.set_value(m_cols.description, description);
}

void
ResourcesViewImpl::add_group(const std::string& id,
  const std::string& name,
  const std::string& description)
{
  auto row = *m_tree_store->append();
  row.set_value(m_cols.id, id);
  row.set_value(m_cols.name, name);
  row.set_value(m_cols.description, description);
}

void
ResourcesViewImpl::delete_resource_or_group ( const int group_index, const int resource_index )
{
  if ( group_index < 0 )
    {
      return;
    }
  Gtk::TreePath p;
  p.push_back ( group_index );
  if ( resource_index >= 0 )
    {
      p.push_back ( resource_index );
    }
  auto iter = *m_tree_store->get_iter ( p );
  m_tree_store->erase ( iter );
  enable_add_group ( true );
}

void ResourcesViewImpl::delete_resources(const int group_index, const std::vector<int> &resource_indices)
{
  int count = 0;
  for (const auto i : resource_indices)
  {
    Gtk::TreePath p;
    p.push_back(group_index);
    p.push_back(i - count);
    Log_I << i << "-" << count << "=" << (i - count);
    auto iter = *m_tree_store->get_iter(p);
    m_tree_store->erase(iter);
    count++;
  }
  enable_add_group(true);
}
NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
