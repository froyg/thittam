/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__812d9c96_4850_11e8_9f83_448500dfb04c
#define HIPRO__812d9c96_4850_11e8_9f83_448500dfb04c

#include <string>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ProjectManager
{
public:
  virtual ~ProjectManager () {}

  virtual bool dirty (void) const = 0;

  virtual bool verify (const std::string & file) = 0;
  virtual void create_new (void) = 0;
  virtual void load (const std::string & file) = 0;
  virtual void save (const std::string & file) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__812d9c96_4850_11e8_9f83_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
