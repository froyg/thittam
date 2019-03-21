/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__57eb0a38_4ece_11e8_84f1_448500dfb04c
#define HIPRO__57eb0a38_4ece_11e8_84f1_448500dfb04c

#include "_namespace.h"
#include "project-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ProjectViewImpl : public ProjectView
{
public:
  ProjectViewImpl (
    hipro::log::Logger* logger,
    Glib::RefPtr<Gtk::Builder> builder);
  ~ProjectViewImpl () {}

  /*--- ProjectView interface ---*/
  Gtk::Widget* widget (void)
  {
    return m_top_widget;
  }

  void set_handler (ProjectViewCallbacks* handler)
  {
    m_handler = handler;
  }
  void attach_content (Gtk::Widget* widget);

private:
  void cb_on_wbs_clicked (void);
  void cb_on_resources_clicked (void);
  void cb_on_gantt_clicked (void);
  void cb_on_resource_usage_clicked (void);

private:
  hipro::log::Logger* logger = nullptr;
  Glib::RefPtr<Gtk::Builder> m_builder;

  ProjectViewCallbacks* m_handler = nullptr;

  Gtk::Widget* m_top_widget = nullptr;
  Gtk::Box* m_container = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__57eb0a38_4ece_11e8_84f1_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
