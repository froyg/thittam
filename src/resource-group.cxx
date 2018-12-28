/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <iostream>

#include "resource-group.h"

NAMESPACE__THITTAM__START

Resource &
ResourceGroup::_get_resource (const int index)
{
  return *std::next(m_resources.begin (), index);
}

const Resource &
ResourceGroup::get_resource (const int index) const
{
  return *std::next(m_resources.begin (), index);
}

void
ResourceGroup::renumber_ids (void)
{
  for (auto & it : m_resources)
  {
    id_counter++;
    it.set_id(std::to_string(id_counter));
  }
}

void
ResourceGroup::create_resource_id (void)
{
  if (id_counter - m_resources.size() > SIZE_COUNTER_DIFFERENCE)
  {
    renumber_ids();
  }
  id_counter++;
}

bool
ResourceGroup::is_unique_resource_name (const std::string & resource_name)
{
  for (auto & it : m_resources)
  {
    if (it.name() == resource_name)
    {
      return false;
    }
  }
  return true;
}

bool
ResourceGroup::add_resource (const std::string & resource_name)
{
  if (!is_unique_resource_name(resource_name))
  {
    return false;
  }

  Resource new_res;
  create_resource_id ();
  new_res.set_id(std::to_string(id_counter));
  new_res.set_name(resource_name);
  m_resources.push_back(new_res);
  return true;
}

bool
ResourceGroup::change_resource_name (
  const int index,
  const std::string & resource_name)
{
  if (is_unique_resource_name(resource_name))
  {
    ResourceGroup::_get_resource(index).Resource::set_name(resource_name);
    return true;
  }
  return false;
}

void
ResourceGroup::change_resource_long_name (
  const int index,
  const std::string & resource_long_name)
{
  ResourceGroup::_get_resource(index).Resource::set_long_name(resource_long_name);
}

void
ResourceGroup::change_resource_cost (
  const int index,
  const float & resource_cost)
{
  ResourceGroup::_get_resource(index).Resource::set_cost(resource_cost);
}

void
ResourceGroup::change_resource_description (
  const int index,
  const std::string & resource_description)
{
  ResourceGroup::_get_resource(index).Resource::set_description(resource_description);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
