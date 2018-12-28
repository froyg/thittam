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

ResourceGroup &
ResourceManager::_get_group (const std::string & id)
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
ResourceManager::_get_group (const int index)
{
  return *std::next(m_resource_groups.begin (), index);
}

const ResourceGroup &
ResourceManager::get_group (const int index) const
{
  return *std::next(m_resource_groups.begin (), index);
}

void
ResourceManager::renumber_ids (void)
{
  for (auto & it : m_resource_groups)
  {
    id_counter++;
    it.set_id(std::to_string(id_counter));
  }
}

void
ResourceManager::create_group_id (void)
{
  if (id_counter - m_resource_groups.size() > SIZE_COUNTER_DIFFERENCE)
  {
    renumber_ids();
  }
  id_counter++;
}

bool
ResourceManager::is_unique_group_name (const std::string & group_name)
{
  for (auto & it : m_resource_groups)
  {
    if (it.name() == group_name)
    {
      return false;
    }
  }
  return true;
}

bool
ResourceManager::add_group (const std::string & group_name)
{
  if (!is_unique_group_name(group_name))
  {
    return false;
  }

  ResourceGroup new_group;
  create_group_id ();
  new_group.set_id(std::to_string(id_counter));
  new_group.set_name(group_name);
  m_resource_groups.push_back(new_group);
  return true;
}

const std::string &
ResourceManager::get_group_id (const int index) const
{
  return get_group(index).id();
}

const std::string &
ResourceManager::get_group_name (const int index) const
{
  return get_group(index).name();
}

const std::string &
ResourceManager::get_group_description (const int index) const
{
  return get_group(index).description();
}

bool
ResourceManager::change_group_name (const int index, const std::string & group_name)
{
  if (is_unique_group_name(group_name))
  {
    ResourceManager::_get_group(index).ResourceGroup::set_name(group_name);
    return true;
  }
  return false;
}

void
ResourceManager::change_group_description (const int index, const std::string & group_description)
{
  ResourceManager::_get_group(index).ResourceGroup::set_description(group_description);
}



const Resource &
ResourceManager::get_resource (const int group_i, const int resource_i) const
{
  return get_group (group_i).get_resource (resource_i);
}

bool
ResourceManager::add_resource (const int index, const std::string & resource_name)
{
  return (ResourceManager::_get_group(index).ResourceGroup::add_resource(resource_name));
}

const std::string &
ResourceManager::get_resource_id (const int group_index, const int resource_index) const
{
  return get_resource(group_index, resource_index).id();
}

const std::string &
ResourceManager::get_resource_name (const int group_index, const int resource_index) const
{
  return get_resource(group_index, resource_index).name();
}

const std::string &
ResourceManager::get_resource_long_name (const int group_index, const int resource_index) const
{
  return get_resource(group_index, resource_index).long_name();
}

const float 
ResourceManager::get_resource_cost (const int group_index, const int resource_index) const
{
  return get_resource(group_index, resource_index).cost();
}

const std::string &
ResourceManager::get_resource_description (const int group_index, const int resource_index) const
{
  return get_resource(group_index, resource_index).description();
}

bool
ResourceManager::change_resource_name (const int group_index, const int resource_index, const std::string & resource_name)
{
  ResourceManager::_get_group(group_index).ResourceGroup::change_resource_name(resource_index, resource_name);
}

void
ResourceManager::change_resource_long_name (const int group_index, const int resource_index, const std::string & resource_long_name)
{
  ResourceManager::_get_group(group_index).ResourceGroup::change_resource_long_name(resource_index, resource_long_name);
}

void
ResourceManager::change_resource_cost (const int group_index, const int resource_index, const float & resource_cost)
{
  ResourceManager::_get_group(group_index).ResourceGroup::change_resource_cost(resource_index, resource_cost);
}

void
ResourceManager::change_resource_description (const int group_index, const int resource_index, const std::string & resource_description)
{
  ResourceManager::_get_group(group_index).ResourceGroup::change_resource_description(resource_index, resource_description);
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
