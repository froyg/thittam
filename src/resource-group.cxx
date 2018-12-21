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

Resource &
ResourceGroup::get_resource (const int index)
{
  return *std::next(m_resources.begin (), index);
}

const Resource &
ResourceGroup::add_resource (void)
{
  Resource new_res = Resource();
  new_res.Resource::set_id(std::to_string(m_resources.size() + 1));
  new_res.Resource::set_name("insert resource name here");
  new_res.Resource::set_cost(0.0);
  m_resources.push_back(new_res);
  return m_resources.back();
}

void
ResourceGroup::change_resource_id (const int index, const std::string & resource_id)
{
  auto resource = ResourceGroup::get_resource(index);
  resource.Resource::set_id(resource_id);
}

void
ResourceGroup::change_resource_name (const int index, const std::string & resource_name)
{
  auto resource = ResourceGroup::get_resource(index);
  resource.Resource::set_name(resource_name);
}

void
ResourceGroup::change_resource_cost (const int index, const float & resource_cost)
{
  auto resource = ResourceGroup::get_resource(index);
  resource.Resource::set_cost(resource_cost);
}


NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
