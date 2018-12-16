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

auto
ResourceGroup::get_resource (const std::string & id) const
{
  for (auto it = m_resources.begin(); it != m_resources.end(); it++)
  {
    if (it->Resource::id() == id)
    {
      return it;
    }
  }
}

const std::string &
ResourceGroup::get_resource_name (const std::string & id) const
{
  auto it = get_resource(id);
  return it->Resource::name();
}

void
ResourceGroup::add_resource (void)
{
  Resource new_res = Resource();
  new_res.Resource::set_id("id");
  new_res.Resource::set_name("name");
  new_res.Resource::set_cost(0.0);
  m_resources.push_back(new_res);
}

void
ResourceGroup::remove_resource (const std::string & id)
{
  auto it = get_resource(id);
  m_resources.erase(it);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
