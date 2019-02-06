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

#include <memory>

#include "resources-controller.h"
#include "resources-view.h"
#include "resource-manager.h"
#include "resource-mvc-factory.h"
#include "resource-group-mvc-factory.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourcesControllerImpl
  : public ResourcesController, public ResourcesViewCallbacks
{
public:
  ResourcesControllerImpl (
    hipro::log::Logger* logger,
    std::unique_ptr<ResourceMVCFactory> resource_mvc_factory,
    std::unique_ptr<ResourceGroupMVCFactory> resource_group_mvc_factory );
  ~ResourcesControllerImpl() {}

  /*--- DI ---*/
  void
  set_view ( std::unique_ptr<ResourcesView> view )
  {
    m_view = std::move ( view );
  }

  void
  set_rm ( std::unique_ptr<ResourceManager> rm )
  {
    m_rm = std::move ( rm );
  }

  /*--- ResourcesController interface ---*/
  Gtk::Widget*
  view_widget ( void )
  {
    return m_view->widget();
  }

  // Called when a node is selected
  void view_node_selected ( const Gtk::TreeModel::Path&, const Gtk::TreeRow& );
  void view_node_changed ( const Gtk::TreeModel::Path&, const Gtk::TreeRow& );

  void view_add_resource_clicked ( void );
  void view_add_group_clicked ( void );
  void view_delete_clicked ( void );

private:
  void add_resource_done ( ResourceController::DoneType done_type );
  void add_resource_group_done ( ResourceGroupController::DoneType done_type );

private:
  hipro::log::Logger* logger = nullptr;
  std::unique_ptr<ResourceMVCFactory> m_resource_mvc_factory;
  std::unique_ptr<ResourceGroupMVCFactory> m_resource_group_mvc_factory;

  int group_index = -1;
  std::string group_id = "";
  std::string resource_id = "";

  std::unique_ptr<ResourcesView> m_view;
  std::unique_ptr<ResourceManager> m_rm;

  Resource m_resource;
  std::unique_ptr<ResourceController> m_resource_controller;
  ResourceGroup m_resource_group;
  std::unique_ptr<ResourceGroupController> m_resource_group_controller;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__123e5b40_5a93_11e8_a7b6_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
