/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__74ae38e2_fd94_11e2_878f_001f3c9e2082
#define HIPRO_THITTAM__74ae38e2_fd94_11e2_878f_001f3c9e2082

#include <memory>

/* ConfigSource provides a way to read and write content to the
 * persistent configuration. This is used by Config to access the
 * persistent configuration. */
class ConfigSource
{
public:
  /* Method to read the entire configuration */
  virtual const std::string & read (void) = 0;

  /* Method to push the configuration into the persistent store */
  virtual void write (const std::string & data) = 0;

  /* dtor */
  virtual ~ConfigSource () {}
};


/* Class to parse and maintain the configuration */
class Config
{
public:
  /* Methods to set and retrieve the serial-port */
  virtual void set_server_address (const std::string & server_address) = 0;
  virtual const std::string & server_address (void) const = 0;

  /* Copy operator */
  virtual void operator= (const Config & other) = 0;

  /* dtor */
  virtual ~Config () {}
};

#endif // HIPRO_THITTAM__74ae38e2_fd94_11e2_878f_001f3c9e2082

/*
  Local Variables:
  mode: c++
  End:
*/
