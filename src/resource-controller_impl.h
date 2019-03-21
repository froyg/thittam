/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__f01a1b22_2796_11e9_89ee_448500dfb04c
#define HIPRO__f01a1b22_2796_11e9_89ee_448500dfb04c

#include <memory>

#include "resource-controller.h"
#include "resource-view.h"
#include "resource.h"

#include "log.h"

NAMESPACE__THITTAM__START

class ResourceControllerImpl :
  public ResourceController,
  public ResourceViewCallbacks
{
public:
  ResourceControllerImpl (hipro::log::Logger* logger);

  /*--- DI ---*/
  void set_view (std::unique_ptr<ResourceView> view)
  {
    m_view = std::move (view);
  }

  void set_model (Resource* model)
  {
    m_model = model;
  }

  /*--- ResourceController interface ---*/
  void show (OnDoneCallbackType on_done_callback);
  void hide (void);

  /*--- ResourceViewCallbacks interface ---*/
  void view_save_pressed (void);
  void view_cancel_pressed (void);

private:
  hipro::log::Logger* logger = nullptr;

  std::unique_ptr<ResourceView> m_view;
  Resource* m_model = nullptr;

  OnDoneCallbackType m_on_done_callback;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__f01a1b22_2796_11e9_89ee_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
