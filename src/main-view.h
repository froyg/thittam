/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__c992faf8_fd96_11e2_9900_001f3c9e2082
#define HIPRO_THITTAM__c992faf8_fd96_11e2_9900_001f3c9e2082

#include <memory>

#include <gtkmm.h>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class MainViewCallbacks
{
public:
  virtual ~MainViewCallbacks () {}

  virtual void view_close_pressed (void) = 0;
  virtual void view_file_new_pressed (void) = 0;
  virtual void view_file_open_pressed (void) = 0;
  virtual void view_file_save_pressed (void) = 0;
  virtual void view_file_save_as_pressed (void) = 0;

};

class MainView
{
public:
  virtual ~MainView () {}

  /* Accessor for the main application window */
  virtual Gtk::Window * window (void) = 0;
  virtual void show (void) = 0;
  virtual bool get_file_to_open (std::string * file_name) = 0;
  virtual bool get_file_to_save (std::string * file_name) = 0;
  virtual bool get_file_to_save_as (std::string * file_name) = 0;
  virtual bool confirm_data_discard (
    const std::string & title,
    const std::string & description) = 0;
  virtual void show_error (const std::string & msg) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO_THITTAM__c992faf8_fd96_11e2_9900_001f3c9e2082

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
