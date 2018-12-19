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

ResourceGroup
ResourceManager::get_group (const std::string & id) const
{
  for (auto it = m_resource_groups.begin(); it != m_resource_groups.end(); it++)
  {
    if (it->id() == id)
    {
      return *it;
    }
  }
  throw ("Invalid Id");
}

const ResourceGroup &
ResourceManager::add_group (void)
{
  ResourceGroup new_res_group = ResourceGroup();
  new_res_group.ResourceGroup::set_id(std::to_string(m_resource_groups.size() + 1));
  new_res_group.ResourceGroup::set_name("name");
  m_resource_groups.push_back(new_res_group);
  return m_resource_groups.back();
}

const Resource &
ResourceManager::add_resource (const std::string & id)
{
  try
  {
    return (ResourceManager::get_group(id).ResourceGroup::add_resource());
  }
  catch (std::exception& e)
  {
    throw (e.what());
  }
}



NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
