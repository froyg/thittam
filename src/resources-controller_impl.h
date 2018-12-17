/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__123e5b40_5a93_11e8_a7b6_448500dfb04c
#define HIPRO__123e5b40_5a93_11e8_a7b6_448500dfb04c

#include "resources-controller.h"
#include "resources-view.h"
#include "resource-manager.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourcesControllerImpl
  : public ResourcesController, public ResourcesViewCallbacks
{
public:
  ResourcesControllerImpl (hipro::log::Logger* logger);
  ~ResourcesControllerImpl () {}

  /*--- DI ---*/
  void set_view (std::unique_ptr<ResourcesView> view)
  {
    m_view = std::move (view);
  }

  void set_rm (std::unique_ptr<ResourceManager> rm)
  {
    m_rm = std::move (rm);
  }

  /*--- ResourcesController interface ---*/
  Gtk::Widget * view_widget (void)
  {
    return m_view->widget ();
  }

  void view_node_selected ();
  void view_node_changed ();

  void view_add_resource_clicked (void);
  void view_add_group_clicked (void);
  void view_delete_clicked (void);

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<ResourcesView> m_view;
  std::unique_ptr<ResourceManager> m_rm;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__123e5b40_5a93_11e8_a7b6_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
