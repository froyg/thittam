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

namespace
{
  Task::Path gtk_tree_path_to_task_path (const Gtk::TreeModel::Path & path)
  {
    Task::Path opath;
    for (auto index : path)
    {
      opath.push_back (index);
    }
    return opath;
  }

  Gtk::TreeModel::Path task_path_to_gtk_tree_path (const Task::Path & path)
  {
    Gtk::TreeModel::Path opath;
    const auto & parts = path.parts ();
    for (auto index : parts)
    {
      opath.push_back (index);
    }
    return opath;
  }
}

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

  builder->get_widget ("tb-cut", m_btn_cut);
  m_btn_cut->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_cut_clicked));
  m_btn_cut->set_sensitive (false);

  builder->get_widget ("tb-copy", m_btn_copy);
  m_btn_copy->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_copy_clicked));
  m_btn_copy->set_sensitive (false);

  builder->get_widget ("tb-paste", m_btn_paste);
  m_btn_paste->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_paste_clicked));
  m_btn_paste->set_sensitive (false);

  builder->get_widget ("tb-delete", m_btn_delete);
  m_btn_delete->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_delete_clicked));
  m_btn_delete->set_sensitive (false);

  builder->get_widget ("tb-indent", m_btn_indent);
  m_btn_indent->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_indent_clicked));
  m_btn_indent->set_sensitive (false);

  builder->get_widget ("tb-unindent", m_btn_unindent);
  m_btn_unindent->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_unindent_clicked));
  m_btn_unindent->set_sensitive (false);

  builder->get_widget ("tb-up", m_btn_up);
  m_btn_up->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_up_clicked));
  m_btn_up->set_sensitive (false);

  builder->get_widget ("tb-down", m_btn_down);
  m_btn_down->signal_clicked ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_down_clicked));
  m_btn_down->set_sensitive (false);

  m_action_group = Gio::SimpleActionGroup::create ();

  m_action_add_child = m_action_group->add_action (
    "add-child",
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_add_child_clicked));

  m_action_add_sibling = m_action_group->add_action (
    "add-sibling",
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_add_sibling_clicked));

  m_action_indent = m_action_group->add_action (
    "indent-task",
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_indent_clicked));

  m_action_unindent = m_action_group->add_action (
    "unindent-task",
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_unindent_clicked));

  m_action_add_child->set_enabled (true);
  m_action_add_sibling->set_enabled(false);
  m_action_indent->set_enabled(false);
  m_action_unindent->set_enabled(false);

  m_top_widget->insert_action_group ("wbs", m_action_group);

  builder->get_widget ("wbspopup", m_menu);
  builder->get_widget ("menu-add-child", m_menu_add_child);
  builder->get_widget ("menu-add-sibling", m_menu_add_sibling);
  builder->get_widget ("menu-indent", m_menu_indent);
  builder->get_widget ("menu-unindent", m_menu_unindent);
  m_menu_add_child->set_sensitive (true);
  m_menu_add_sibling->set_sensitive (false);
  m_menu_indent->set_sensitive (false);
  m_menu_unindent->set_sensitive (false);

  /* Fix the tree-view */
  m_tree_store = Gtk::TreeStore::create (m_cols);
  m_tree_view.set_model (m_tree_store);

  m_tree_view.append_column ("ID", m_cols.id);
  m_tree_view.append_column_editable ("Title", m_cols.title);
  m_tree_view.append_column_editable ("Effort", m_cols.effort);

  m_tree_view.signal_button_press_event ().connect_notify
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_button_pressed));
  m_tree_view.signal_row_activated ().connect
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_row_activated));

  m_tree_store->signal_row_changed ().connect (
    sigc::mem_fun (*this, &WBSViewImpl::cb_on_row_changed));

  m_tree_selection = m_tree_view.get_selection ();
  m_tree_selection->signal_changed ().connect
    (sigc::mem_fun (*this, &WBSViewImpl::cb_on_row_selected));

  Gtk::ScrolledWindow * tree_container = nullptr;
  builder->get_widget ("tree-container", tree_container);
  tree_container->add (m_tree_view);

  Gtk::Box* top_box = dynamic_cast<Gtk::Box*> (m_top_widget);
  top_box->show_all_children ();
}

void
WBSViewImpl::enable_add_child (bool enable)
{
  m_action_add_child->set_enabled (enable);
  m_menu_add_child->set_sensitive (enable);
}

void
WBSViewImpl::enable_add_sibling (bool enable)
{
  m_action_add_sibling->set_enabled (enable);
  m_menu_add_sibling->set_sensitive (enable);
}

void
WBSViewImpl::enable_indent_task (bool enable)
{
  m_action_indent->set_enabled (enable);
  m_menu_indent->set_sensitive (enable);
  m_btn_indent->set_sensitive (enable);
}

void
WBSViewImpl::enable_unindent_task (bool enable)
{
  m_action_unindent->set_enabled (enable);
  m_menu_unindent->set_sensitive (enable);
  m_btn_unindent->set_sensitive (enable);
}

void
WBSViewImpl::enable_up (bool enable)
{
  m_btn_up->set_sensitive (enable);
}

void
WBSViewImpl::enable_down (bool enable)
{
  m_btn_down->set_sensitive (enable);
}

void
WBSViewImpl::enable_cut (bool enable)
{
  m_btn_cut->set_sensitive (enable);
}

void
WBSViewImpl::enable_copy (bool enable)
{
  m_btn_copy->set_sensitive (enable);
}

void
WBSViewImpl::enable_paste (bool enable)
{
  m_btn_paste->set_sensitive (enable);
}

void
WBSViewImpl::enable_delete (bool enable)
{
  m_btn_delete->set_sensitive (enable);
}

void
WBSViewImpl::add_child (const Task::Path & t_path)
{
  Log_I << "add_child ";
  auto g_path = task_path_to_gtk_tree_path (t_path);
  auto it = m_tree_store->get_iter (g_path);
  auto child = m_tree_store->append (it->children ());
  auto & row = *child;
  row[m_cols.id] = "aa";
  Log_D << "g_path " << g_path.size ();
}


// Indent a selected node towards the right i.e. append the current node to the
// end of its previous sibling's children.
// it should be valid and also have a valid previous sibling.
void
WBSViewImpl::indent (const Task::Path & t_path)
{
  Log_I << "[WBSViewImpl] Indent";
  auto g_path = task_path_to_gtk_tree_path(t_path);
  auto old_node = m_tree_store->get_iter (g_path);
  auto prev_sibling = (--old_node)++;

  // Create a node at the end of its previous sibling's children
  auto &new_node = *m_tree_store->append (prev_sibling->children());

  // Copy all the tasks from old_node to new_node
  copy_task(*old_node, new_node);
  copy_sub_tasks(*old_node, new_node);

  // Delete the current node
  m_tree_store->erase (old_node);

  // Expand the subtree else we wont be able to select the new_node
  m_tree_view.expand_row(m_tree_store->get_path(prev_sibling), false);
  m_tree_selection->select (new_node);
}

// Unindent a given node towards the left
void
WBSViewImpl::unindent (const Task::Path & t_path)
{
  Log_I << "[WBSViewImpl] Unindent";
  auto g_path = task_path_to_gtk_tree_path (t_path);
  auto old_node = m_tree_store->get_iter (g_path);
  auto parent_node = old_node->parent();

  // Create a new sibling of parent node
  auto &new_node = *m_tree_store->insert_after (parent_node->children());

  // Copy all the tasks from old_node to new_node
  copy_task(*old_node, new_node);
  copy_sub_tasks(*old_node, new_node);

  // Delete the current node
  m_tree_store->erase (old_node);

  // Select the newly created node
  m_tree_selection->select (new_node);
}

// Renumbers all task IDs. Call this after the wbs tree is modified.
void
WBSViewImpl::renumber (void)
{
  auto children = m_tree_store;
  int index = 1;
  std::string id;
  for (auto child : m_tree_store->children ())
  {
    do_renumber (&(*child), id, index);
    index += 1;
  }
}

void
WBSViewImpl::do_renumber (
  const Gtk::TreeRow * row, const std::string & parent_id, int index)
{
  std::ostringstream os;
  if (! parent_id.empty ())
  {
    os << parent_id << ".";
  }
  os << index;
  auto id = os.str ();
  (*row)[m_cols.id] = id;

  index = 1;
  for (auto child : row->children ())
  {
    auto iter = &(*child);
    do_renumber (iter, id, index);
    index +=1;
  }
}

void
WBSViewImpl::cb_on_row_selected (void)
{
  auto gtk_paths = m_tree_selection->get_selected_rows ();
  std::vector<Task::Path> task_paths;

  for (auto & g_path : gtk_paths)
  {
    auto t_path = gtk_tree_path_to_task_path (g_path);
    task_paths.push_back (t_path);
  }

  m_handler->view_node_selected (std::move (task_paths));

  m_menu_add_sibling->set_sensitive (true);
  m_menu_indent->set_sensitive (true);
  m_menu_unindent->set_sensitive (true);

  m_action_add_child->set_enabled (true);
  m_action_add_sibling->set_enabled(true);
  m_action_indent->set_enabled(true);
  m_action_unindent->set_enabled(true);
}

void
WBSViewImpl::cb_on_button_pressed (GdkEventButton * event)
{
  if (((int)event->type == (int)Gdk::BUTTON_PRESS) && (event->button == 3))
    {
      if (!m_menu->get_attach_widget ())
      {
        m_menu->attach_to_widget (m_tree_view);
      }
      m_menu->popup (event->button, event->time);
    }
}

void
WBSViewImpl::cb_on_row_activated (
  const Gtk::TreeModel::Path & path,
  Gtk::TreeViewColumn * column)
{
  // auto it = m_tree_selection->get_selected ();
  // std::string chosen_id;
  // it->get_value (0, chosen_id);

  // m_handler->view_node_activated (chosen_id);
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
WBSViewImpl::cb_on_indent_clicked (void)
{
  m_handler->view_indent_clicked();
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
WBSViewImpl::cb_on_row_changed (
  const Gtk::TreeModel::Path& path,
  const Gtk::TreeModel::iterator& iter)
{
  if (m_self_change)
  {
    return;
  }

  Log_D << "Path: " << path.to_string ();
}

void
WBSViewImpl::copy_sub_tasks(
  const Gtk::TreeRow &source,
  const Gtk::TreeRow &destination)
{
  for (auto &old_child : source.children())
  {
    auto &new_child = *m_tree_store->append (destination->children());
    copy_task(old_child, new_child);
    copy_sub_tasks (old_child, new_child);
  }
}

inline void
WBSViewImpl::copy_task(
  const Gtk::TreeRow &source,
  const Gtk::TreeRow &destination)
{
  destination.set_value(m_cols.id, source.get_value(m_cols.id));
  destination.set_value(m_cols.title, source.get_value(m_cols.title));
  destination.set_value(m_cols.effort, source.get_value(m_cols.effort));
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
