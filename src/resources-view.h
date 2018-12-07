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

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ResourcesViewCallbacks
{
public:
  virtual ~ResourcesViewCallbacks () {}

  virtual void view_node_selected (
                                   std::vector<WBS::Path> && path_list) = 0;
  virtual void view_node_activated (
                                    const WBS::Path & path) = 0;

  virtual void view_add_resource_clicked (void) = 0;
  virtual void view_add_resource_group_clicked (void) = 0;
  virtual void view_cut_clicked (void) = 0;
  virtual void view_copy_clicked (void) = 0;
  virtual void view_paste_clicked (void) = 0;
  virtual void view_delete_clicked (void) = 0;
  virtual void view_up_clicked (void) = 0;
  virtual void view_down_clicked (void) = 0;
};

class ResourcesView
{
public:
  virtual ~ResourcesView () {}

  virtual Gtk::Widget* widget (void) = 0;

  virtual void set_handler (ResourcesViewCallbacks* handler) = 0;
  
  virtual void enable_add_resource (bool enable) = 0;
  virtual void enable_add_resource_group (bool enable) = 0;
  virtual void enable_up (bool enable) = 0;
  virtual void enable_down (bool enable) = 0;
  virtual void enable_cut (bool enable) = 0;
  virtual void enable_copy (bool enable) = 0;
  virtual void enable_paste (bool enable) = 0;
  virtual void enable_delete (bool enable) = 0;

  virtual void add_resource (const WBS::Path & path) = 0;
  virtual void add_resource_group (const WBS::Path & t_path) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__0bc8374a_5a93_11e8_af85_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
