/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__db56ba7c_fd96_11e2_806c_001f3c9e2082
#define HIPRO_THITTAM__db56ba7c_fd96_11e2_806c_001f3c9e2082

#include <memory>

#include <gtkmm.h>

#include "common.h"
#include "main-view.h"
#include "log.h"

NAMESPACE__THITTAM__START

class MainViewImpl : public MainView
{
public:
  MainViewImpl (
    hipro::log::Logger* logger,
    Glib::RefPtr<Gtk::Builder> builder);
  ~MainViewImpl () { }

  /*--- DI ---*/
  void set_handler (MainViewCallbacks * handler)
  {
    m_handler = handler;
  }

  /*--- MainView interface ---*/
  Gtk::Window * window (void)
  {
    return m_window;
  }
  void attach_content (Gtk::Widget* widget);

  void show (void);
  bool get_file_to_open (std::string * file_name);
  bool get_file_to_save (std::string * file_name);
  bool get_file_to_save_as (std::string * file_name);
  bool confirm_data_discard (
    const std::string & title, const std::string & description);
  void show_error (const std::string & msg);

private:
  void cb_on_file_new (void);
  void cb_on_file_open (void);
  void cb_on_file_save (void);
  void cb_on_file_save_as (void);
  void cb_on_close (void);

private:
  hipro::log::Logger* logger = nullptr;
  Glib::RefPtr<Gtk::Builder> m_builder;

  MainViewCallbacks* m_handler = nullptr;

  Gtk::Window* m_window = nullptr;
  Gtk::Box* m_container = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO_THITTAM__db56ba7c_fd96_11e2_806c_001f3c9e2082

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
