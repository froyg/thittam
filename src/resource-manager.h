/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c
#define HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

#include <vector>
#include <string>

#include "_namespace.h"
#include "ResourceGroup.h"

NAMESPACE__THITTAM__START

class ResourceManager
{
public:
  // TODO

private:
  std::vector<std::unique_ptr<ResourceGroup>> m_resource_group;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
