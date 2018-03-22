/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

NAMESPACE__THITTAM__START

#define MIN_ZOOM 1
#define MAX_ZOOM 20

void
GANTTView::add_task (const std::string & id, int days, int order, int depth)
{
  auto item = std::make_unique<scene::BoxItem> (days);
  auto item_raw = item.get ();
  m_items.insert (std::make_pair (id, std::move (item)));

  // assuming top-level task
  m_item_raw->move (order, depth);
  m_scene->add_item (m_item_raw);
}

void
GANTTView::on_draw (Cairo::RefPtr<Cairo::Context> context)
{
  m_scene->render (context);
}

void
GANTTView::on_zoom_in (void)
{
  if (m_factor < MAX_ZOOM)
  {
    m_factor ++;
    m_scene->scale (m_factor);
  }
}

void
GANTTView::on_zoom_out (void)
{
  if (m_factor > MIN_ZOOM)
  {
    m_factor --;
    m_scene->scale (m_factor);
  }
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
