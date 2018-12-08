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

// auto
// ResourceGroup::get_resource (const std::string & id)
// {
//   for(auto it = m_resources.begin(); it != m_resources.end(); it++)
//   {
//     if (it->resource_id() == id){
//       return it;
//     }
//   }
// }

const std::string &
ResourceGroup::get_resource_name (const std::string & id) const
{
  for(auto it = m_resources.begin(); it != m_resources.end(); it++)
  {
    if (it->resource_id() == id){
      return it->resource_name();
    }
  }
}

// void
// ResourceGroup::add_resource (const std::string & id, const std::string & name, const float cost)
// {
//   Resource new_res = Resource();
//   new_res.set_resource_id(id);
//   new_res.set_resource_name(name);
//   new_res.set_resource_cost(cost);
//   m_resources.push_back(new_res);
// }

// void
// ResourceGroup::remove_resource (const std::string & id)
// {
//   auto it = get_resource(id);
//   m_resources.erase(it);
// }

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
