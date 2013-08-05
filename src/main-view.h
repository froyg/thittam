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

#include <boost/signals2.hpp>


class MainView
{
public:
  typedef std::shared_ptr<MainView> ptr_t;

  /* Signal raised when the user wants to close the application */
  typedef ::boost::signals2::signal <
    void (void)
    > signal_close_t;

public:
  /* Methods to access the signals */
  virtual signal_close_t & signal_close (void) = 0;

  /* Accessor for the main application window */
  virtual Gtk::Window * window (void) = 0;

  /* virtual dtor */
  virtual ~MainView () {}
};

#endif // HIPRO_THITTAM__c992faf8_fd96_11e2_9900_001f3c9e2082

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
