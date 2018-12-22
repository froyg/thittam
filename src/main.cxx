/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <memory>

#include "app_impl.h"
#include "util.h"

int
main (int argc, char ** argv)
{
  thittam::util::init_random ();
  auto app = std::make_shared<thittam::AppImpl> ();
  int ret = app->run (argc, argv);
  return ret;
}

/*
  Local Variables:
  mode: c++
  End:
*/
