/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__a3803906_3e1a_11e8_a2ad_448500dfb04c
#define HIPRO__a3803906_3e1a_11e8_a2ad_448500dfb04c

#include "_namespace.h"
#include "wbs.h"

NAMESPACE__THITTAM__START

class WBSTreeModel
{
public:
  virtual
  ~WBSTreeModel() {}

  virtual WBS::Path
  convert_gtk_tree_path_to_wbs_path(
    const Gtk::TreeModel::Path& path) = 0;
  virtual WBS::Path
  convert_gtk_tree_iter_to_wbs_path(
    const Gtk::TreeModel::iterator& it) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__a3803906_3e1a_11e8_a2ad_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
