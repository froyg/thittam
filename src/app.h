/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__3d643ed2_fd93_11e2_a635_001f3c9e2082
#define HIPRO_THITTAM__3d643ed2_fd93_11e2_a635_001f3c9e2082

#include <memory>

#include <boost/signals2.hpp>

class App
{
public:
  typedef ::std::shared_ptr<App> ptr_t;

public:
  /* Method to run the App. This does not return until the
   * application is closed */
  virtual int run (int argc, char **argv) = 0;

  /* Request the application to quit. The application will not quit
   * immediately. It'll quit at the earliest. */
  virtual void quit (void) = 0;

  /* dtor */
  virtual ~App () {}
};

class SubApp
{
public:
  typedef ::std::shared_ptr<SubApp> ptr_t;
  typedef std::weak_ptr<SubApp> weak_ptr_t;

  /* Signal raised when the sub-app is closed */
  typedef ::boost::signals2::signal <
    void (void)
    > signal_closed_t;

public:
  /* Accessor for the signal-closed */
  virtual signal_closed_t & signal_closed (void) = 0;

  /* Method to start the SubApp  */
  virtual void start (void) = 0;

  /* Method to force a SubApp to stop. This is called before the
   * SubApp is destroyed */
  virtual void stop (void) = 0;

  /* dtor */
  virtual ~SubApp () {}
};

#endif // HIPRO_THITTAM__3d643ed2_fd93_11e2_a635_001f3c9e2082

/*
  Local Variables:
  mode: c++
  End:
*/
