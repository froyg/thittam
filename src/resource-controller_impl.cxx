/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resource-controller_impl.h"

NAMESPACE__THITTAM__START

ResourceControllerImpl::ResourceControllerImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

void
ResourceControllerImpl::show (OnDoneCallbackType on_done_callback)
{
  m_on_done_callback = on_done_callback;
  m_view->set_short_name (m_model->name ());
  m_view->set_long_name (m_model->long_name ());
  m_view->set_cost (m_model->cost ());
  m_view->set_description (m_model->description ());

  m_view->show ();
}

void
ResourceControllerImpl::hide (void)
{
  m_view->hide ();
}

void
ResourceControllerImpl::view_save_pressed (void)
{
  m_model->set_name (m_view->short_name ());
  m_model->set_long_name (m_view->long_name ());
  m_model->set_cost (m_view->cost ());
  m_model->set_description (m_view->description ());

  m_on_done_callback (DoneType::SAVE);
}

void
ResourceControllerImpl::view_cancel_pressed (void)
{
  m_on_done_callback (DoneType::CANCEL);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
