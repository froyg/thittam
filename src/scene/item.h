/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__2292d45e_2d42_11e8_8f5b_448500dfb04c
#define HIPRO__2292d45e_2d42_11e8_8f5b_448500dfb04c

#include <cairommconfig.h>
#include <cairomm/context.h>

#include "_namespace.h"

NAMESPACE__THITTAM_SCENE__START

class Item
{
public:
  virtual ~Item () {}

  virtual void move (int x, int y) = 0;
  virtual void scale (int x_factor, int y_factor) = 0;
  virtual void render (Cairo::RefPtr<Cairo::Context> context) = 0;
};

NAMESPACE__THITTAM_SCENE__END

#endif // HIPRO__2292d45e_2d42_11e8_8f5b_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
