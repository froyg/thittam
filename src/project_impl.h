/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__cf54ac8c_4195_11e8_be66_448500dfb04c
#define HIPRO__cf54ac8c_4195_11e8_be66_448500dfb04c

#include <memory>

#include "log.h"
#include "project.h"
#include "wbs.h"

NAMESPACE__THITTAM__START

class ProjectImpl : public Project
{
public:
  ~ProjectImpl() {}
  ProjectImpl(hipro::log::Logger* logger);

  /*--- DI ---*/
  void
  set_wbs(std::unique_ptr<WBS> wbs)
  {
    m_wbs = std::move(wbs);
  }

  /*--- Project interface ---*/
  const std::string&
  name(void) const
  {
    return m_name;
  }

  WBS*
  wbs(void) const
  {
    return m_wbs.get();
  }

  bool
  dirty(void) const;
  void
  clear_dirty(void);
  bool
  check(const boost::property_tree::ptree& data) const;
  void
  load(const boost::property_tree::ptree& data) const;
  boost::property_tree::ptree
  serialize(void);

private:
  hipro::log::Logger* logger = nullptr;
  std::string m_name;

  std::unique_ptr<WBS> m_wbs;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__cf54ac8c_4195_11e8_be66_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
