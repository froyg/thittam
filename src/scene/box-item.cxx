/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "box-item.h"

NAMESPACE__THITTAM_SCENE__START

BoxItem::BoxItem (int width)
  : m_width (width)
{

}

void
BoxItem::move (int x, int y)
{
  m_sx = x;
  m_sy = y;
  m_dirty = true;
}

void
BoxItem::scale (int x_factor, int y_factor)
{
  m_x_scaling_factor = x_factor;
  m_y_scaling_factor = y_factor;
  m_dirty = true;
}

void
BoxItem::compute (void)
{
  if (m_dirty == false)
  {
    return;
  }

  m_x1 = m_sx * m_x_scaling_factor;
  m_y1 = m_sy * m_y_scaling_factor;

  m_x2 = m_x1 + (m_width * m_x_scaling_factor);
  m_y2 = m_y1 + (1 * m_y_scaling_factor); // Our height is always 1 unit

  m_dirty = false;
}

void
BoxItem::render (Cairo::RefPtr<Cairo::Context> context)
{
  // line(m_x1, m_y1, m_x2, m_y1);
  // line(m_x2, m_y1, m_x2, m_y2);
  // line(m_x2, m_y2, m_x1, m_y2);
  // line(m_x1, m_y2, m_x1, m_y1);
  // paint_region();
}

NAMESPACE__THITTAM_SCENE__END

/*
  Local Variables:
  mode: c++
  End:
*/
