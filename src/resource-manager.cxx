/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resource-manager.h"

NAMESPACE__THITTAM__START

void
ResourceManager::add_group (void)
{
  ResourceGroup new_res_group = ResourceGroup();
  new_res_group.ResourceGroup::set_id("id");
  new_res_group.ResourceGroup::set_name("name");
  m_resource_groups.push_back(new_res_group);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
