/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__3323dfa2_2d42_11e8_b123_448500dfb04c
#define HIPRO__3323dfa2_2d42_11e8_b123_448500dfb04c

#include "_namespace.h"
#include "item.h"

NAMESPACE__THITTAM_SCENE__START

NAMESPACE__THITTAM_SCENE__START

class BoxItem : public Item
{
public:
  BoxItem (int width);

  /*--- Item interface ---*/
  void move (int x, int y);
  void scale (int x_factor, int y_factor);
  void render (Cairo::RefPtr<Cairo::Context> context);

private:
  void compute (void);

private:
  int m_width = 0;

  bool m_dirty = true;
  int m_sx = 0;
  int m_sy = 0;
  int m_x_scaling_factor = 1;
  int m_y_scaling_factor = 1;

  int m_x1 = 0;
  int m_y1 = 0;
  int m_x2 = 0;
  int m_y2 = 0;
};

NAMESPACE__THITTAM_SCENE__END

#endif // HIPRO__3323dfa2_2d42_11e8_b123_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
