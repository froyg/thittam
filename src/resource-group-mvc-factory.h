/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__703d7e0a_27a8_11e9_b278_448500dfb04c
#define HIPRO__703d7e0a_27a8_11e9_b278_448500dfb04c

#include <memory>

#include "_namespace.h"
#include "resource-group-controller.h"
#include "resource-group.h"
#include "resource-manager.h"

NAMESPACE__THITTAM__START

class ResourceGroupMVCFactory
{
public:
  virtual
  ~ResourceGroupMVCFactory() {}

  virtual std::unique_ptr<ResourceGroupController>
  create(ResourceGroup* model, const ResourceManager& groups) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__703d7e0a_27a8_11e9_b278_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
