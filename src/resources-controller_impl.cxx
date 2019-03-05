/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resources-controller_impl.h"

NAMESPACE__THITTAM__START

ResourcesControllerImpl::ResourcesControllerImpl(
  hipro::log::Logger* logger,
  std::unique_ptr<ResourceMVCFactory> resource_mvc_factory,
  std::unique_ptr<ResourceGroupMVCFactory> resource_group_mvc_factory)
  : logger(logger),
    m_resource_mvc_factory(std::move(resource_mvc_factory)),
    m_resource_group_mvc_factory(std::move(resource_group_mvc_factory))
{

}

void
ResourcesControllerImpl::view_node_selected(
  const Gtk::TreeModel::Path& path,
  const Gtk::TreeRow& row)
{
  bool f = m_view->node_is_selected(path);
  m_view->enable_add_resource(f);
  m_view->enable_delete(f);
  if (f == true) {
    group_index = path[0];
    const auto& id = m_view->get_id(row);
    if (m_view->selected_is_group()) {
      group_id = id;
      resource_id = "";
    } else {
      group_id = m_view->get_id(*row.parent());
      resource_id = id;
    }
  } else {
    group_index = -1;
    group_id = resource_id = "";
  }
}

void
ResourcesControllerImpl::view_node_changed(
  const Gtk::TreeModel::Path& path,
  const Gtk::TreeRow& row)
{
  // Don't do anything if nothing is selected
  if (!m_view->node_is_selected(path)) {
    return;
  }

  // if (m_view->selected_is_group ())
  // {
  //   if (m_rm->change_group_id (path[0], m_view->get_id (row)))
  //   {
  //     m_view->set_id (row, m_rm->get_group_id (path[0]));
  //   }
  //   m_rm->change_group_name (path[0], m_view->get_name (row));
  // }
  // else if (path.size () == 2)
  // {
  //   if (m_rm->change_resource_id (path[0], path[1], m_view->get_id (row)))
  //   {
  //     m_view->set_id (row, m_rm->get_resource_id (path[0], path[1]));
  //   }
  //   m_rm->change_resource_name (path[0], path[1], m_view->get_name (row));
  //   m_rm->change_resource_cost (path[0], path[1], m_view->get_cost (row));
  // }
}

void
ResourcesControllerImpl::view_add_resource_clicked(void)
{
  m_resource_controller = m_resource_mvc_factory->create(&m_resource);
  m_resource_controller->show(
    std::bind(&ResourcesControllerImpl::add_resource_done, this,
      std::placeholders::_1));
}

void
ResourcesControllerImpl::add_resource_done(
  ResourceController::DoneType done_type)
{
  if (done_type == ResourceController::DoneType::CANCEL) {
    m_resource_controller->hide();
    m_resource_controller.reset();
    return;
  }
  auto& res = m_resource;
  auto& group = *m_rm->get_resource_group_mutable(group_id);
  if (group.add_resource(res)) {
    m_resource_controller->hide();
    m_resource_controller.reset();
    m_view->add_resource(group_index, res.id(), res.name(), res.cost(),
      res.description());
  }
}

void
ResourcesControllerImpl::view_add_group_clicked(void)
{
  m_resource_group_controller =
    m_resource_group_mvc_factory->create(&m_resource_group);
  m_resource_group_controller->show(
    std::bind(&ResourcesControllerImpl::add_resource_group_done, this,
      std::placeholders::_1));
}

void
ResourcesControllerImpl::add_resource_group_done(
  ResourceGroupController::DoneType done_type)
{
  if (done_type == ResourceGroupController::DoneType::CANCEL) {
    m_resource_group_controller->hide();
    m_resource_group_controller.reset();
    return;
  }
  auto& group = m_resource_group;
  if (m_rm->add_group(group)) {
    m_resource_group_controller->hide();
    m_resource_group_controller.reset();
    m_view->add_group(group.id(), group.name(), group.description());
  }
}

void
ResourcesControllerImpl::view_delete_clicked(void)
{
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
