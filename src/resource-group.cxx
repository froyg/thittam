/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resource-group.h"

NAMESPACE__THITTAM__START

bool
ResourceGroup::validate_resources_id (const std::string & resource_id)
{
  for (auto & it : m_resources)
  {
    if (it.id() == resource_id)
    {
      return false;
    }
  }
  return true;
}

std::string
ResourceGroup::generate_unique_resource_id (void)
{
  // In case number of resources is more than MOD_MAX
  // generating unique id would not be possible
  if (m_resources.size() < MOD_MAX)
  {
    std::string id = util::generate_random_id();
    for (; !ResourceGroup::validate_resources_id(id) ; )
    {
      id = util::generate_random_id();
    }
    return id;
  }
  return FAILED_TO_GENERATE_RANDOM_ID;
}

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

const Resource &
ResourceGroup::add_resource (void)
{
  std::string id = ResourceGroup::generate_unique_resource_id();

  if (id != FAILED_TO_GENERATE_RANDOM_ID)
  {
    Resource new_res = Resource();
    new_res.Resource::set_id(id);
    m_resources.push_back(new_res);
    return m_resources.back();
  }

  throw "Unable to generate id";
}

bool
ResourceGroup::change_resource_id (
  const int index,
  const std::string & resource_id)
{
  if (ResourceGroup::validate_resources_id(resource_id))
  {
    ResourceGroup::_get_resource(index).Resource::set_id(resource_id);
    return true;
  }
  return false;
}

void
ResourceGroup::change_resource_name (
  const int index,
  const std::string & resource_name)
{
  ResourceGroup::_get_resource(index).Resource::set_name(resource_name);
}

void
ResourceGroup::change_resource_cost (
  const int index,
  const float & resource_cost)
{
  ResourceGroup::_get_resource(index).Resource::set_cost(resource_cost);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
