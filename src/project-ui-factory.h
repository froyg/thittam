/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__8f866cd4_4e11_11e8_b24a_448500dfb04c
#define HIPRO__8f866cd4_4e11_11e8_b24a_448500dfb04c

#include <memory>

#include "_namespace.h"
#include "project.h"
#include "project-controller.h"

NAMESPACE__THITTAM__START

/* Produces the entire Project UI. The Project UI comprises of all the SubViews
 * that are shown in the content area of the ProjectView. This takes care of
 * creating it. */
class ProjectUIFactory
{
public:
  virtual
  ~ProjectUIFactory() {}

  virtual std::unique_ptr<ProjectController>
  create(Project* project) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__8f866cd4_4e11_11e8_b24a_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
