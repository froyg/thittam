/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resource-group-controller_impl.h"

NAMESPACE__THITTAM__START

ResourceGroupControllerImpl::ResourceGroupControllerImpl(
  hipro::log::Logger* logger)
  : logger(logger)
{

}

void
ResourceGroupControllerImpl::show(OnDoneCallbackType on_done_callback)
{
  m_on_done_callback = on_done_callback;
  m_view->set_name(m_model->name());
  m_view->set_description(m_model->description());

  m_view->show();
}

void
ResourceGroupControllerImpl::hide(void)
{
  m_view->hide();
}

void
ResourceGroupControllerImpl::view_group_name_changed(void)
{
  m_view->enable_save(m_rm->is_unique_group_name(m_view->name()));
}

void
ResourceGroupControllerImpl::view_save_pressed(void)
{
  m_model->set_name(m_view->name());
  m_model->set_description(m_view->description());

  m_on_done_callback(DoneType::SAVE);
}

void
ResourceGroupControllerImpl::view_cancel_pressed(void)
{
  m_on_done_callback(DoneType::CANCEL);
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
