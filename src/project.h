/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__cdfe836c_4195_11e8_b8b8_448500dfb04c
#define HIPRO__cdfe836c_4195_11e8_b8b8_448500dfb04c

#include <boost/property_tree/ptree.hpp>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class Project
{
public:
  virtual ~Project () {}

  virtual bool dirty (void) const = 0;
  virtual void clear_dirty (void) = 0;

  virtual bool check (const boost::property_tree::ptree & data) const = 0;
  virtual void load (const boost::property_tree::ptree & data) const = 0;
  virtual boost::property_tree::ptree serialize (void) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__cdfe836c_4195_11e8_b8b8_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
