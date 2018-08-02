/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__e8aa0cd4_59c5_11e8_b3d4_448500dfb04c
#define HIPRO__e8aa0cd4_59c5_11e8_b3d4_448500dfb04c

#include <gtkmm.h>

#include "_namespace.h"
#include "task.h"

NAMESPACE__THITTAM__START

class WBSViewCallbacks
{
public:
  virtual ~WBSViewCallbacks () {}

  virtual void view_node_selected (
    std::vector<Task::Path> && path_list) = 0;
  virtual void view_node_activated (
    const Task::Path & path) = 0;

  virtual void view_add_child_clicked (void) = 0;
  virtual void view_add_sibling_clicked (void) = 0;
  virtual void view_cut_clicked (void) = 0;
  virtual void view_copy_clicked (void) = 0;
  virtual void view_paste_clicked (void) = 0;
  virtual void view_delete_clicked (void) = 0;
  virtual void view_indent_clicked (void) = 0;
  virtual void view_unindent_clicked (void) = 0;
  virtual void view_up_clicked (void) = 0;
  virtual void view_down_clicked (void) = 0;
};

class WBSView
{
public:
  virtual ~WBSView () {}

  virtual Gtk::Widget* widget (void) = 0;

  virtual void set_handler (WBSViewCallbacks* handler) = 0;

  virtual void add_child (const Task::Path & path) = 0;
  virtual void indent (const Task::Path & path) = 0;
  virtual void unindent (const Task::Path & Path) = 0;
  virtual void renumber (void) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__e8aa0cd4_59c5_11e8_b3d4_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
