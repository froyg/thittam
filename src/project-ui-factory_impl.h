/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__52ba3810_4ebd_11e8_b8eb_448500dfb04c
#define HIPRO__52ba3810_4ebd_11e8_b8eb_448500dfb04c

#include <gtkmm.h>

#include "log.h"
#include "project-ui-factory.h"

NAMESPACE__THITTAM__START

class ProjectUIFactoryImpl : public ProjectUIFactory
{
public:
  ProjectUIFactoryImpl (hipro::log::Logger* logger);
  ~ProjectUIFactoryImpl () {}

  /*--- DI ---*/
  void set_parent_window (Gtk::Window* window)
  {
    m_parent_window = window;
  }

  /*--- ProjectUIFactory interface ---*/
  std::unique_ptr<ProjectController> create (Project * project);

private:
  hipro::log::Logger* logger = nullptr;

  Gtk::Window* m_parent_window = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__52ba3810_4ebd_11e8_b8eb_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
