/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__66cb9258_27a8_11e9_ba63_448500dfb04c
#define HIPRO__66cb9258_27a8_11e9_ba63_448500dfb04c

#include <memory>

#include "resource-group-controller.h"
#include "resource-group-view.h"
#include "resource-group.h"
#include "resource-manager.h"

#include "log.h"

NAMESPACE__THITTAM__START

class ResourceGroupControllerImpl : public ResourceGroupController,
  public ResourceGroupViewCallbacks
{
public:
  ResourceGroupControllerImpl(hipro::log::Logger* logger);

  /*--- DI ---*/
  void
  set_view(std::unique_ptr<ResourceGroupView> view)
  {
    m_view = std::move(view);
  }

  void
  set_model(ResourceGroup* model)
  {
    m_model = model;
  }
  void
  set_helper_model(const ResourceManager& model)
  {
    m_rm = &model;
  }

  /*--- ResourceGroupController interface ---*/
  void
  show(OnDoneCallbackType on_done_callback);
  void
  hide(void);

  /*--- ResourceGroupViewCallbacks interface ---*/
  void
  view_group_name_changed(void);
  void
  view_save_pressed(void);
  void
  view_cancel_pressed(void);

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<ResourceGroupView> m_view;
  const ResourceManager* m_rm;
  ResourceGroup* m_model = nullptr;

  OnDoneCallbackType m_on_done_callback;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__66cb9258_27a8_11e9_ba63_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
