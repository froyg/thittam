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
  typedef std::shared_ptr<RequirementImpl> ptr_t;

public:
  /* ------- ctor/dtor ----------- */
  RequirementImpl (HLogPtr logger);
  RequirementImpl (HLogPtr logger, const std::string & id,
                   const std::string & title, const std::string & description);
  ~RequirementImpl () {}

  static ptr_t create (HLogPtr logger, const std::string & id,
                       const std::string & title,
                       const std::string & description)
  {
    ptr_t object (new RequirementImpl (logger, id, title, description));
    return object;
  }

  static ptr_t create (HLogPtr logger)
  {
    ptr_t object (new RequirementImpl (logger));
    return object;
  }

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

  Requirement::ptr_t parent (void)
  {
    return m_parent.lock ();
  }

  void set_id (const std::string & id)
  {
    m_id = id;
  }

  void set_title (const std::string & title)
  {
    m_title = title;
  }

  void set_description (const std::string & description)
  {
    m_description = description;
  }

  void set_parent (Requirement::ptr_t parent)
  {
    m_parent = parent;
  }

  void add_child (Requirement::ptr_t child);
  void remove_child (Requirement::ptr_t child);
  void add_depends (Requirement::ptr_t depends);
  void remove_depends (Requirement::ptr_t depends);

private:
  HLogPtr m_logger;
  std::string m_id;
  std::string m_title;
  std::string m_description;
  Requirement::weak_ptr_t m_parent;
  std::vector<Requirement::ptr_t> m_children;
  std::vector<Requirement::ptr_t> m_depends;
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
