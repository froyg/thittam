/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__e2abab08_286a_11e8_9b53_448500dfb04c
#define HIPRO__e2abab08_286a_11e8_9b53_448500dfb04c

#include <list>

#include <gtkmm.h>

#include "_namespace.h"
#include "wbs-tree-model.h"
#include "wbs.h"

NAMESPACE__THITTAM__START

class WBSGtkTreeModelGlueItem
{
public:
  WBSGtkTreeModelGlueItem(const WBS::Path& path)
    : m_path(path)
  {
  }

  const WBS::Path&
  path(void) const
  {
    return m_path;
  }

private:
  WBS::Path m_path;
};


class WBSGtkTreeModel : public WBSTreeModel,
  public WBSObserver,
  public Gtk::TreeModel
{
public:
  typedef WBSGtkTreeModelGlueItem GlueItem;

public:
  WBSGtkTreeModel();
  ~WBSGtkTreeModel() {}

  /*--- WBSTreeModel interface ---*/
  WBS::Path
  convert_gtk_tree_path_to_wbs_path(
    const Gtk::TreeModel::Path& path);
  WBS::Path
  convert_gtk_tree_iter_to_wbs_path(
    const Gtk::TreeModel::iterator& it);

  /*--- WBSObserver interface ---*/
  void
  wbs_observer_node_inserted(const WBS::Path& path);
  void
  wbs_observer_node_changed(const WBS::Path& path);
  void
  wbs_observer_node_deleted(const WBS::Path& path);
  void
  wbs_observer_node_reordered(
    const WBS::Path& path, const std::vector<int>& new_order);

  /*--- Gtk::TreeModel interface ---*/
  Gtk::TreeModelFlags
  get_flags_vfunc() const;
  int
  get_n_columns_vfunc() const;
  GType
  get_column_type_vfunc(int index) const;

  bool
  iter_next_vfunc(
    const iterator& iter, iterator& iter_next) const;

  bool
  get_iter_vfunc(const Path& path, iterator& iter) const;
  bool
  iter_children_vfunc(
    const iterator& parent, iterator& iter) const;
  bool
  iter_parent_vfunc(const iterator& child, iterator& iter) const;
  bool
  iter_nth_child_vfunc(
    const iterator& parent, int n, iterator& iter) const;
  bool
  iter_nth_root_child_vfunc(int n, iterator& iter) const;
  bool
  iter_has_child_vfunc(const iterator& iter) const;
  int
  iter_n_children_vfunc(const iterator& iter) const;
  int
  iter_n_root_children_vfunc() const;
  void
  ref_node_vfunc(const iterator& iter) const;
  void
  unref_node_vfunc(const iterator& iter) const;
  TreeModel::Path
  get_path_vfunc(const iterator& iter) const;
  void
  get_value_vfunc(
    const iterator& iter, int column, Glib::ValueBase& value) const;
  void
  set_value_impl(
    const iterator& row, int column, const Glib::ValueBase& value);

private:
  Gtk::TreeModel::Path
  convert_wbs_path_to_gtk_tree_path(
    const WBS::Path& path);
  Gtk::TreeModel::iterator
  convert_wbs_path_to_gtk_tree_iter(
    const WBS::Path& path);

private:
  std::list<GlueItem> m_glue_item_list;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e2abab08_286a_11e8_9b53_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
