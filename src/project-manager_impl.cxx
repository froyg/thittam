/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "project-manager_impl.h"

NAMESPACE__THITTAM__START

bool
ProjectManagerImpl::dirty (void) const
{
  return true;
}

bool
ProjectManagerImpl::verify (const std::string & file)
{
  return m_project_factory->verify (file);
}

void
ProjectManagerImpl::create_new (void)
{
  /* If a project is already loaded, we should cleanly unload it */
  if (m_project_controller)
  {
    m_project_controller->detach_ui ();
    m_project_controller.reset ();
  }

  m_project = m_project_factory->create ();
  m_project_controller = m_project_ui_factory->create (m_project.get ());
  m_project_controller->attach_ui ();
}

void
ProjectManagerImpl::load (const std::string & file)
{
  /* If a project is already loaded, we should cleanly unload it */
  if (m_project_controller)
  {
    m_project_controller->detach_ui ();
    m_project_controller.reset ();
  }

  m_project = m_project_factory->create (file);
  m_project_controller = m_project_ui_factory->create (m_project.get ());
  m_project_controller->attach_ui ();
}

void
ProjectManagerImpl::save (const std::string & file)
{
  m_project->save (file);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
