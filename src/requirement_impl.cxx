/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "requirement_impl.h"

RequirementImpl::RequirementImpl (HLogPtr logger) :
  m_logger (logger)
{

}

RequirementImpl::RequirementImpl
(HLogPtr logger, const std::string & id, const std::string & title,
 const std::string & description) :
  m_logger (logger),
  m_id (id),
  m_title (title),
  m_description (description)
{

}

void
RequirementImpl::add_child (Requirement::ptr_t child)
{
  /* TBD: Should we check whether the given child already in the
     children list? */
  child->set_parent (shared_from_this ());
  m_children.push_back (child);
}

void
RequirementImpl::remove_child (Requirement::ptr_t child)
{
  auto end = m_children.end ();
  for (auto it = m_children.begin (); it != end; ++it)
    {
      if ((*it)->id () == child->id ())
        {
          m_children.erase (it);
          return;
        }
    }
  ASSERT ((false), "Requirement=%s not found", child->id ().c_str ());
}

void
RequirementImpl::add_depends (Requirement::ptr_t depends)
{
  /* TBD: Should we check whether the given requirement is already on
     the dependency list? */
  m_depends.push_back (depends);
}

void
RequirementImpl::remove_depends (Requirement::ptr_t depends)
{
  auto end = m_depends.end ();
  for (auto it = m_depends.begin (); it != end; ++it)
    {
      if ((*it)->id () == depends->id ())
        {
          m_depends.erase (it);
          return;
        }
    }
  ASSERT ((false), "Requirement=%s not found", depends->id ().c_str ());
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/