/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <fstream>

#include "resource-manager.h"

NAMESPACE__THITTAM__START

bool
ResourceManager::validate_group_id (const std::string & group_id)
{
  for (auto & it : m_resource_groups)
  {
    if (it.id() == group_id)
    {
      return false;
    }
  }
  return true;
}

std::string
ResourceManager::generate_unique_group_id (void)
{
  // In case number of groups is more than MOD_MAX
  // generating unique id would not be possible
  if (m_resource_groups.size() < MOD_MAX)
  {
    std::string id = util::generate_random_id();
    for (; !ResourceManager::validate_group_id(id) ; )
    {
      id = util::generate_random_id();
    }
    return id;
  }
  return FAILED_TO_GENERATE_RANDOM_ID;
}

ResourceGroup &
ResourceManager::get_group (const std::string & id)
{
  for (auto & it : m_resource_groups)
  {
    if (it.id() == id)
    {
      return it;
    }
  }
  throw ("Invalid Id");
}

ResourceGroup &
ResourceManager::get_group (const int index)
{
  return *std::next(m_resource_groups.begin (), index);
}

const ResourceGroup &
ResourceManager::add_group (void)
{
  std::string id = ResourceManager::generate_unique_group_id();
  if (id != FAILED_TO_GENERATE_RANDOM_ID)
  {
    ResourceGroup new_res_group = ResourceGroup();
    new_res_group.ResourceGroup::set_id(id);
    new_res_group.ResourceGroup::set_name("name");
    m_resource_groups.push_back(new_res_group);
    return m_resource_groups.back();
  }
}

const Resource &
ResourceManager::add_resource (const std::string & group_id)
{
  return (ResourceManager::get_group(group_id).ResourceGroup::add_resource());
}

bool
ResourceManager::change_group_id (const int index, const std::string & group_id)
{

  if (ResourceManager::validate_group_id(group_id))
  {
    ResourceManager::get_group(index).ResourceGroup::set_id(group_id);
    return true;
  }
  return false;
}

void
ResourceManager::change_group_name (const int index, const std::string & group_name)
{
  ResourceManager::get_group(index).ResourceGroup::set_name(group_name);
}

bool
ResourceManager::change_resource_id (const int group_index, const int resource_index, const std::string & resource_id)
{
  return ResourceManager::get_group(group_index).ResourceGroup::change_resource_id(resource_index, resource_id);
}

void
ResourceManager::change_resource_name (const int group_index, const int resource_index, const std::string & resource_name)
{
  ResourceManager::get_group(group_index).ResourceGroup::change_resource_name(resource_index, resource_name);
}

void
ResourceManager::change_resource_cost (const int group_index, const int resource_index, const float & resource_cost)
{
  ResourceManager::get_group(group_index).ResourceGroup::change_resource_cost(resource_index, resource_cost);
}

void
ResourceManager::generate_json (void)
{
  // WIP
  std::ofstream outFile;
  outFile.open("new.json");

  for (auto & it : m_resource_groups)
  {
    outFile << it.ResourceGroup::id() << "\n";
    outFile << it.ResourceGroup::name() << "\n";
  }
  outFile.close();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
