/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__6e29bb4c_2d8f_11e8_a4ef_448500dfb04c
#define HIPRO__6e29bb4c_2d8f_11e8_a4ef_448500dfb04c

#include <cairommconfig.h>
#include <cairomm/context.h>

#include "scene/box-item.h"

#include "_namespace.h"

NAMESPACE__THITTAM__START

class GANTTView
{
public:
  void add_task (const std::string & id, int days);

private:
  void on_zoom_in (void);
  void on_zoom_out (void);
  void on_draw (Cairo::RefPtr<Cairo::Context> context);

private:
  std::map<std::string, std::unique_ptr<Item>> m_items;
  scene::Graph * m_scene = nullptr;

  int m_factor = 10;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__6e29bb4c_2d8f_11e8_a4ef_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
