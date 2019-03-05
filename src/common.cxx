/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <boost/date_time/c_local_time_adjustor.hpp>

#include "common.h"

typedef boost::date_time::c_local_adjustor<bpot::ptime> local_adj;

bpot::ptime
utc_to_local(const bpot::ptime& pt)
{
  return local_adj::utc_to_local(pt);
}

bpot::ptime
local_to_utc(const bpot::ptime& pt)
{
  bpot::ptime ref_utc_time(bgre::date(2013, 01, 01), bpot::hours(0));
  auto ref_local_time = utc_to_local(ref_utc_time);

  bpot::time_duration tdiff = ref_local_time - ref_utc_time;
  return (pt - tdiff);
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
