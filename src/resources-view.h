/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__0bc8374a_5a93_11e8_af85_448500dfb04c
#define HIPRO__0bc8374a_5a93_11e8_af85_448500dfb04c

#include <gtkmm.h>
#include <vector>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ResourcesViewCallbacks
{
public:
  virtual
  ~ResourcesViewCallbacks() {}

  virtual void
  view_node_selected(const std::vector<Gtk::TreeModel::Path>&) = 0;
  virtual void
  view_node_changed(const Gtk::TreeModel::Path&, const Gtk::TreeRow&) = 0;

  virtual void
  view_add_resource_clicked(void) = 0;
  virtual void
  view_add_group_clicked(void) = 0;
  virtual void
  view_delete_clicked(void) = 0;
};

class ResourcesView
{
public:
  virtual
  ~ResourcesView() {}

  virtual Gtk::Widget*
  widget(void) = 0;

  virtual void
  set_handler(ResourcesViewCallbacks* handler) = 0;

  virtual const Gtk::TreeIter
  path_to_rowiter(const Gtk::TreePath& p) = 0;

  virtual bool
  node_is_selected(const Gtk::TreeModel::Path&) = 0;
  virtual bool
  is_group(const Gtk::TreeModel::Path&) = 0;

  virtual void
  set_id(const Gtk::TreeRow&, const std::string&) = 0;
  virtual void
  set_name(const Gtk::TreeRow&, const std::string&) = 0;
  virtual void
  set_cost(const Gtk::TreeRow&, const float) = 0;

  virtual std::string
  get_id(const Gtk::TreeIter) = 0;
  virtual std::string
  get_name(const Gtk::TreeIter) = 0;
  virtual float
  get_cost(const Gtk::TreeIter) = 0;

  virtual void
  enable_add_resource(bool enable) = 0;
  virtual void
  enable_add_group(bool enable) = 0;
  virtual void
  enable_delete(bool enable) = 0;

  virtual void
  add_resource(const int, const std::string&, const std::string&, const float,
    const std::string&) = 0;
  virtual void
  add_group(const std::string&, const std::string&, const std::string&) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__0bc8374a_5a93_11e8_af85_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
