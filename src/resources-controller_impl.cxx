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

void ResourcesControllerImpl::view_node_selected ()
{
}

void ResourcesControllerImpl::view_node_changed ()
{
}

void ResourcesControllerImpl::view_add_resource_clicked (void)
{
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
