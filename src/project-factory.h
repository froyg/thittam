/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__b24c0f2e_4e13_11e8_ad61_448500dfb04c
#define HIPRO__b24c0f2e_4e13_11e8_ad61_448500dfb04c

#include <memory>
#include <string>

#include "_namespace.h"
#include "project.h"

NAMESPACE__THITTAM__START

class ProjectFactory
{
public:
  virtual ~ProjectFactory () {}

  virtual bool verify (const std::string & file) const = 0;
  virtual std::unique_ptr<Project> create (void) const = 0;
  virtual std::unique_ptr<Project> create (
    const std::string & file_name) const = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__b24c0f2e_4e13_11e8_ad61_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
