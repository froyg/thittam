/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__050997e8_ff51_11e2_a1fa_68a3c42125fd
#define HIPRO_THITTAM__050997e8_ff51_11e2_a1fa_68a3c42125fd

#include <memory>
#include <string>

#include "requirement.h"

class ReqView
{
public:
  /* Show form to get new requirement */
  virtual int show (void) = 0;
  /* Show the existing requirement */
  virtual int show (std::shared_ptr<Requirement> req) = 0;
  /* Hide the requirement form dialog */
  virtual void hide (void) = 0;
  virtual std::string title (void) = 0;
  virtual std::string description (void) = 0;
  virtual std::string work (void) = 0;
};

#endif // HIPRO_THITTAM__050997e8_ff51_11e2_a1fa_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
