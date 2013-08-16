/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__5dd9f5ac_00e6_11e3_beb6_68a3c42125fd
#define HIPRO_THITTAM__5dd9f5ac_00e6_11e3_beb6_68a3c42125fd

#include <vector>

#include "common.h"
#include "requirement.h"

class RequirementImpl : public std::enable_shared_from_this<RequirementImpl>,
                        public Requirement
{
public:
  /* ------- ctor/dtor ----------- */
  RequirementImpl (HLogPtr logger)
  : m_logger (logger)
  { }
  ~RequirementImpl () {}

  /* ------- Methods required by the interface ----------- */
  const std::string & id (void) const
  {
    return m_id;
  }

  const std::string & title (void) const
  {
    return m_title;
  }

  const std::string & description (void) const
  {
    return m_description;
  }

  std::shared_ptr<Requirement> parent (void) const
  {
    return m_parent.lock ();
  }

  void set_title (const std::string & title)
  {
    m_title = title;
  }

  void set_description (const std::string & description)
  {
    m_description = description;
  }

  requirement_list_t::const_iterator children_cbegin (void) const
  {
    return m_children.cbegin ();
  }

  requirement_list_t::const_iterator children_cend (void) const
  {
    return m_children.cend ();
  }

  requirement_list_t::const_iterator depends_cbegin (void) const
  {
    return m_depends.cbegin ();
  }

  requirement_list_t::const_iterator depends_cend (void) const
  {
    return m_depends.cend ();
  }

  void set_id (const std::string & id)
  {
    m_id = id;
  }

  void set_parent (std::shared_ptr<Requirement> parent)
  {
    m_parent = parent;
  }

  requirement_list_t * children (void)
  {
    return &m_children;
  }

  requirement_list_t * depends (void)
  {
    return &m_depends;
  }

private:
  HLogPtr m_logger;

  std::string m_id;
  std::string m_title;
  std::string m_description;

  std::weak_ptr<Requirement> m_parent;
  std::vector<std::shared_ptr<Requirement>> m_children;
  std::vector<std::shared_ptr<Requirement>> m_depends;
};

class RequirementFactoryImpl
{
public:
  RequirementFactoryImpl (HLogPtr logger)
  : m_logger (logger)
  {
  }

  std::shared_ptr<Requirement> create (void)
  {
    return std::make_shared<RequirementImpl> (m_logger);
  }

  std::shared_ptr<Requirement>
  create (const std::string & title, const std::string & description)
  {
    auto obj = std::make_shared<RequirementImpl> (m_logger);
    obj->set_title (title);
    obj->set_description (description);
    return obj
  }

  std::shared_ptr<Requirement>
  create (const std::string & id, const std::string & title,
          const std::string & description)
  {
    auto obj = std::make_shared<RequirementImpl> (m_logger);
    obj->set_id (id);
    obj->set_title (title);
    obj->set_description (description);
    return obj
  }

private:
  HLogPtr m_logger;
};

#endif // HIPRO_THITTAM__5dd9f5ac_00e6_11e3_beb6_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
