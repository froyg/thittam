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
  m_resources.push_back(new_res);
  return m_resources.back();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
