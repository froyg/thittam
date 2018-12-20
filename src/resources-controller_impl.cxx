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

ResourcesControllerImpl::ResourcesControllerImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

void ResourcesControllerImpl::view_node_selected (
  const Gtk::TreeModel::Path &path,
  const Gtk::TreeRow &row)
{
  bool f = m_view->node_is_selected (path);
  m_view->enable_add_resource (f);
  m_view->enable_delete (f);
  if (f)
  {
    group_index = path[0];
    if (m_view->selected_is_group ())
    {
      resource_index = -1;
    }
    else
    {
      resource_index = path[1];
    }
  }
  else
  {
    group_index = resource_index = -1;
  }
}

void ResourcesControllerImpl::view_node_changed (
  const Gtk::TreeModel::Path &path,
  const Gtk::TreeRow &row)
{
  // Don't do anything if nothing is selected
  if (!m_view->node_is_selected (path))
  {
    return;
  }

  ResourceGroup &rg = m_rm->get_group (path[0]);
  if (m_view->selected_is_group ())
  {
    rg.set_id (m_view->get_id (row));
    rg.set_name (m_view->get_name (row));
  }
  else if (path.size () == 2)
  {
    Resource &r = rg.get_resource (path[1]);
    r.set_id (m_view->get_id (row));
    r.set_name (m_view->get_name (row));
    r.set_cost (m_view->get_cost (row));
  }
}

void ResourcesControllerImpl::view_add_resource_clicked (void)
{
  int gi = group_index;
  if (gi == -1)
  {
    return;
  }
  ResourceGroup &rg = m_rm->get_group (gi);
  const Resource &r = rg.add_resource ();
  m_view->add_resource (gi, r.id (), r.name (), r.cost ());
}

void ResourcesControllerImpl::view_add_group_clicked (void)
{
  Log_I << "Adding new group";
  const ResourceGroup &r = m_rm->add_group ();
  m_view->add_group (r.id (), r.name ());
}

void ResourcesControllerImpl::view_delete_clicked (void)
{
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
