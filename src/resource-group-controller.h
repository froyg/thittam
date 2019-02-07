/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__655b24c4_27a8_11e9_b0ba_448500dfb04c
#define HIPRO__655b24c4_27a8_11e9_b0ba_448500dfb04c

#include <functional>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class ResourceGroupController
{
public:
  enum class DoneType
    {
      SAVE = 1,
      CANCEL = 2,
    };
  typedef std::function<void (DoneType)> OnDoneCallbackType;

public:
  ~ResourceGroupController () {}

  virtual void show (OnDoneCallbackType on_done_callback) = 0;
  virtual void hide (void) = 0;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__655b24c4_27a8_11e9_b0ba_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
