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

auto
ResourceManager::get_group (const std::string & id) const
{
  for (auto it = m_resource_groups.begin(); it != m_resource_groups.end(); it++)
  {
    if (it->ResourceGroup::id() == id)
    {
      return it;
    }
  }
}

const std::string &
ResourceManager::get_group_name (const std::string & id) const
{
  auto it = ResourceManager::get_group(id);
  return it->ResourceGroup::name();
}

void
ResourceManager::add_group (const std::string & id, const std::string & name)
{
  ResourceGroup new_res_group = ResourceGroup();
  new_res_group.ResourceGroup::set_id(id);
  new_res_group.ResourceGroup::set_name(name);
  m_resource_groups.push_back(new_res_group);
}

void
ResourceManager::remove_group (const std::string & id)
{
  auto it = ResourceManager::get_group(id);
  m_resource_groups.erase(it);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
