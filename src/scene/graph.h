/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__f8e121f8_2d44_11e8_93c2_448500dfb04c
#define HIPRO__f8e121f8_2d44_11e8_93c2_448500dfb04c

#include <cairommconfig.h>
#include <cairomm/context.h>

#include "_namespace.h"

NAMESPACE__THITTAM_SCENE__START

class Graph
{
public:
  void add_item (Item * item);
  void remove_item (Item * item);
  void scale (int factor);
  void render (Cairo::RefPtr<Cairo::Context> context);

private:
  int m_x_scaling_factor = 10;
  int m_y_scaling_factor = 5;
};

NAMESPACE__THITTAM_SCENE__END

#endif // HIPRO__f8e121f8_2d44_11e8_93c2_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
