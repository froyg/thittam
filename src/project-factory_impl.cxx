/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "project-factory_impl.h"
#include "project_impl.h"
#include "wbs_impl.h"

NAMESPACE__THITTAM__START

ProjectFactoryImpl::ProjectFactoryImpl(hipro::log::Logger* logger)
  : logger(logger)
{

}

bool
ProjectFactoryImpl::verify(const std::string& file) const
{
  // todo: verify the contents of the given file
  return false;
}

std::unique_ptr<Project>
ProjectFactoryImpl::create(void) const
{
  auto wbs = std::make_unique<WBSImpl> (logger);
  auto project = std::make_unique<ProjectImpl> (logger);
  project->set_wbs(std::move(wbs));
  return project;
}

std::unique_ptr<Project>
ProjectFactoryImpl::create(const std::string& file_name) const
{
  throw std::runtime_error("not implemented");
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
