/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__df71450c_27a0_11e9_9874_448500dfb04c
#define HIPRO__df71450c_27a0_11e9_9874_448500dfb04c

#include <memory>

#include "_namespace.h"
#include "resource-controller.h"
#include "resource.h"

NAMESPACE__THITTAM__START

class ResourceMVCFactory
{
public:
  virtual ~ResourceMVCFactory () {}

  virtual std::unique_ptr<ResourceController> create (Resource* model) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__df71450c_27a0_11e9_9874_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
