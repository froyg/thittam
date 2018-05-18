/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "project_impl.h"

NAMESPACE__THITTAM__START

ProjectImpl::ProjectImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

bool
ProjectImpl::dirty (void) const
{
  return m_wbs->dirty ();
}

void
ProjectImpl::clear_dirty (void)
{
  m_wbs->clear_dirty ();
}

bool
ProjectImpl::check (const boost::property_tree::ptree & data) const
{
  return true;
}

void
ProjectImpl::load (const boost::property_tree::ptree & data) const
{
  // todo: load the project from the given ptree
}

boost::property_tree::ptree
ProjectImpl::serialize (void)
{
  // todo: serialize the project
  boost::property_tree::ptree pt;
  return pt;
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
