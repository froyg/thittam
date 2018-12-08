/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resources-view_impl.h"

NAMESPACE__THITTAM__START

ResourcesViewImpl::ResourcesViewImpl (
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder)
  : logger (logger)
{
  builder->get_widget ("top-widget", m_top_widget);
  auto parent = m_top_widget->get_parent ();
  if (parent)
  {
    parent->remove (*m_top_widget);
  }
}

void ResourcesViewImpl::enable_add_resource (bool enable)
{
}

void ResourcesViewImpl::enable_add_resource_group (bool enable)
{
}

void ResourcesViewImpl::enable_up (bool enable)
{
}

void ResourcesViewImpl::enable_down (bool enable)
{
}

void ResourcesViewImpl::enable_cut (bool enable)
{
}

void ResourcesViewImpl::enable_copy (bool enable)
{
}

void ResourcesViewImpl::enable_paste (bool enable)
{
}

void ResourcesViewImpl::enable_delete (bool enable)
{
}

void ResourcesViewImpl::add_resource ()
{
}

void ResourcesViewImpl::add_resource_group ()
{
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
