/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__82cb7c80_4850_11e8_9809_448500dfb04c
#define HIPRO__82cb7c80_4850_11e8_9809_448500dfb04c

#include <memory>

#include "log.h"
#include "project-manager.h"
#include "project.h"
#include "project-controller.h"
#include "project-ui-factory.h"
#include "project-factory.h"

NAMESPACE__THITTAM__START

class ProjectManagerImpl : public ProjectManager
{
public:
  ProjectManagerImpl (hipro::log::Logger* logger)
    : logger (logger)
  {
  }

  ~ProjectManagerImpl () {}

  /*--- DI ---*/
  void set_project_factory (ProjectFactory* project_factory)
  {
    m_project_factory = project_factory;
  }

  void set_project_ui_factory (ProjectUIFactory* project_ui_factory)
  {
    m_project_ui_factory = project_ui_factory;
  }

  /*--- ProjectManager interface ---*/
  bool dirty (void) const;
  bool verify (const std::string & file);
  void create_new (void);
  void load (const std::string & file);
  void save (const std::string & file);

private:
  hipro::log::Logger* logger = nullptr;

  ProjectFactory* m_project_factory = nullptr;
  ProjectUIFactory* m_project_ui_factory;

  std::unique_ptr<Project> m_project;
  std::unique_ptr<ProjectController> m_project_controller;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__82cb7c80_4850_11e8_9809_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
