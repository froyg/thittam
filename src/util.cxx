/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "util.h"

NAMESPACE__THITTAM_UTIL__START

int effort_str_to_minutes (
  const std::string & effort, int working_days_per_week,
  int working_hours_per_day)
{
  // todo: issue #8
  return 2400;
}

unsigned int
generate_random_id ()
{
  // For 6 digit random number.
  srand(time(NULL));
  unsigned int number = rand() % MOD_MAX;
  return number;
}

NAMESPACE__THITTAM_UTIL__END

/*
  Local Variables:
  mode: c++
  End:
*/
