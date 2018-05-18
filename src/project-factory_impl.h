/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__b48bfae2_4e13_11e8_bb1f_448500dfb04c
#define HIPRO__b48bfae2_4e13_11e8_bb1f_448500dfb04c

#include <memory>

#include "log.h"
#include "project-factory.h"

NAMESPACE__THITTAM__START

class ProjectFactoryImpl : public ProjectFactory
{
public:
  ProjectFactoryImpl (hipro::log::Logger* logger);
  ~ProjectFactoryImpl () {}

  /*--- ProjectFactory interface ---*/
  bool verify (const std::string & file) const;
  std::unique_ptr<Project> create (void) const;
  std::unique_ptr<Project> create (const std::string & file_name) const;

private:
  hipro::log::Logger* logger = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__b48bfae2_4e13_11e8_bb1f_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
