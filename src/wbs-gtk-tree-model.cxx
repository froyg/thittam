/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "wbs-gtk-tree-model.h"

NAMESPACE__THITTAM__START

WBSGtkTreeModel::WBSGtkTreeModel ()
{

}

WBS::Path
WBSGtkTreeModel::convert_gtk_tree_path_to_wbs_path (
  const Gtk::TreeModel::Path & path)
{
  WBS::Path wbs_path;
  for (auto index : path)
  {
    wbs_path.push_back (index);
  }
  return wbs_path;
}

WBS::Path
WBSGtkTreeModel::convert_gtk_tree_iter_to_wbs_path (
  const Gtk::TreeModel::iterator & it)
{
  auto gobj = it.gobj ();
  auto glue = reinterpret_cast<GlueItem *> (gobj->user_data);
  return glue.path ();
}

void
WBSGtkTreeModel::wbs_observer_node_inserted (const WBS::Path & path)
{
  auto path = convert_wbs_path_to_gtk_tree_path (child);
  auto iter = convert_wbs_path_to_gtk_tree_iter (child);
  row_inserted (path, iter);
}

void
WBSGtkTreeModel::wbs_observer_node_changed (const WBS::Path & path)
{
  auto path = convert_wbs_path_to_gtk_tree_path (child);
  auto iter = convert_wbs_path_to_gtk_tree_iter (child);
  row_changed (path, iter);
}

void
WBSGtkTreeModel::wbs_observer_node_deleted (const WBS::Path & path)
{
  auto path = convert_wbs_path_to_gtk_tree_path (child);
  row_deleted (path);
}

void
WBSGtkTreeModel::wbs_observer_node_reordered (
  const WBS::Path & path, const std::vector<int> & new_order)
{

}

Gtk::TreeModel::Path
WBSGtkTreeModel::convert_wbs_path_to_gtk_tree_path (const WBS::Path & path)
{
  Gtk::TreeModel::Path gtk_path;
  for (auto index : path.parts ())
  {
    gtk_path.push_back (index);
  }
  return gtk_path;
}

Gtk::TreeModel::iterator
WBSGtkTreeModel::convert_wbs_path_to_gtk_tree_iter (const WBS::Path & path)
{
  Gtk::TreeModel::iterator iter;
  auto gobj = iter.gobj ();
  iter.set_stamp (1);

  for (auto & item : m_glue_item_list)
  {
    if (item.path () == path)
    {
      gobj->user_data = &item;
      return iter;
    }
  }

  GlueItem glue (path);
  m_glue_list.push_back (path);
  gobj->user_data = & m_glue_list.back ();
  return iter;
}

/*----------------------------------------------------------------------------*/

Gtk::TreeModelFlags
WBSGtkTreeModel::get_flags_vfunc () const
{
  return Gtk::TreeModelFlags::TREE_MODEL_ITERS_PERSIST;
}

int
WBSGtkTreeModel::get_n_columns_vfunc () const
{
  return 0;
}

GType
WBSGtkTreeModel::get_column_type_vfunc (int index) const
{
  return G_TYPE_STRING;
}

bool
WBSGtkTreeModel::iter_next_vfunc (
  const iterator& iter, iterator& iter_next) const
{
  return false;
}

bool
WBSGtkTreeModel::get_iter_vfunc (const Path& path, iterator& iter) const
{
  return false;
}

bool
WBSGtkTreeModel::iter_children_vfunc (
  const iterator& parent, iterator& iter) const
{
  return false;
}

bool
WBSGtkTreeModel::iter_parent_vfunc (
  const iterator& child, iterator& iter) const
{
  return false;
}

bool
WBSGtkTreeModel::iter_nth_child_vfunc (
  const iterator& parent, int n, iterator& iter) const
{
  return false;
}

bool
WBSGtkTreeModel::iter_nth_root_child_vfunc (int n, iterator& iter) const
{
  return false;
}

bool
WBSGtkTreeModel::iter_has_child_vfunc (const iterator& iter) const
{
  return false;
}

int
WBSGtkTreeModel::iter_n_children_vfunc (const iterator& iter) const
{
  return 0;
}

int
WBSGtkTreeModel::iter_n_root_children_vfunc () const
{
  return 0;
}

void
WBSGtkTreeModel::ref_node_vfunc (const iterator& iter) const
{

}

void
WBSGtkTreeModel::unref_node_vfunc (const iterator& iter) const
{

}

Gtk::TreeModel::Path
WBSGtkTreeModel::get_path_vfunc (const iterator& iter) const
{
  Gtk::TreePath path ("0");
  return path;
}

void
WBSGtkTreeModel::get_value_vfunc (
  const iterator& iter, int column, Glib::ValueBase& value) const
{

}

void
WBSGtkTreeModel::set_value_impl (
  const iterator& row, int column, const Glib::ValueBase& value)
{

}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
