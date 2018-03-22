/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

NAMESPACE__THITTAM_SCENE__START

#include "graph.h"

void
Graph::add_item (Item * item)
{
  item->scale (m_x_scaling_factor, m_y_scaling_factor);
  m_items.push_back (item);
}

void
Graph::remove_item (Item * item)
{
  auto it = std::find (m_items.begin (), m_items.end (), item);
  if (it != m_items.end ())
  {
    m_items.erase (item);
  }
}

void
Graph::scale (int factor)
{
  m_x_scaling_factor = factor;
  m_y_scaling_factor = 5;

  for (auto item : m_items)
  {
    item->scale (m_x_scaling_factor, m_y_scaling_factor);
  }
}

void
Graph::render (Cairo::RefPtr<Cairo::Context> context)
{
  for (auto item : m_items)
  {
    item->render (context);
  }
}

NAMESPACE__THITTAM_SCENE__END

/*
  Local Variables:
  mode: c++
  End:
*/
