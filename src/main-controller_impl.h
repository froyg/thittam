/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__050bad70_3f2b_11e8_b9df_448500dfb04c
#define HIPRO__050bad70_3f2b_11e8_b9df_448500dfb04c

#include "app.h"
#include "log.h"
#include "main-controller.h"
#include "main-view.h"
#include "project-factory.h"
#include "project-ui-factory.h"
#include "project.h"
#include "project-controller.h"

NAMESPACE__THITTAM__START

class MainControllerImpl : public MainController, public MainViewCallbacks
{
public:
  MainControllerImpl(hipro::log::Logger* logger);
  ~MainControllerImpl() {}

  /*--- DI ---*/
  void
  set_view(MainView* view)
  {
    m_view = view;
  }

  void
  set_app(App* app)
  {
    m_app = app;
  }

  void
  set_project_factory(ProjectFactory* project_factory)
  {
    m_project_factory = project_factory;
  }

  void
  set_project_ui_factory(ProjectUIFactory* project_ui_factory)
  {
    m_project_ui_factory = project_ui_factory;
  }

  /*--- MainController interface ---*/
  void
  start(void);

  /*--- MainViewCallbacks interface ---*/
  void
  view_close_pressed(void);
  void
  view_file_new_pressed(void);
  void
  view_file_open_pressed(void);
  void
  view_file_save_pressed(void);
  void
  view_file_save_as_pressed(void);

private:
  bool
  confirm_data_discard(void);
  bool
  can_save_to(const std::string& file_name);
  void
  do_save(void);

private:
  hipro::log::Logger* logger = nullptr;

  MainView* m_view = nullptr;
  App* m_app = nullptr;
  ProjectFactory* m_project_factory = nullptr;
  ProjectUIFactory* m_project_ui_factory = nullptr;

  std::string m_file_name;
  std::unique_ptr<Project> m_project;
  std::unique_ptr<ProjectController> m_project_controller;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__050bad70_3f2b_11e8_b9df_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
