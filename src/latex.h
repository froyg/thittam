/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__98505cfc_0ed9_11e3_a8a9_68a3c42125fd
#define HIPRO_THITTAM__98505cfc_0ed9_11e3_a8a9_68a3c42125fd

#include <memory>
#include <string>

#include "requirement.h"

class Latex
{
public:
  virtual void generate_flat (
    std::shared_ptr<Requirement> req, const std::string & top_level,
    std::ofstream * ofile) = 0;

  virtual void generate_topic_hierarchy (
    std::shared_ptr<Requirement> req, std::ofstream * ofile) = 0;

  /* virtual dtor */
  virtual ~Latex () {}
};

#endif // HIPRO_THITTAM__98505cfc_0ed9_11e3_a8a9_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
