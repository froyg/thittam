/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__1f1ef54a_c2c2_11e2_ab99_001f3c9e2082
#define HIPRO_THITTAM__1f1ef54a_c2c2_11e2_ab99_001f3c9e2082

#include <initializer_list>

#include <boost/date_time.hpp>

#include <hdb/log.h>

#include "error.h"

/*--- A class to safely delete a shared_ptr ---*/
template< class T >
class SafeDeleter { public: void operator()(T * m) { delete m; } };

/*--- Short namespaces ---*/
namespace boost {
  namespace signals2 { }
  namespace filesystem { }
  namespace posix_time { }
  namespace gregorian { }
  namespace property_tree { }
  namespace program_options { }
}

typedef ::hdb::log::Level HLogLevel;
typedef ::hdb::log::Logger HLog;
typedef ::hdb::log::Logger::ptr_type HLogPtr;

namespace bsig = ::boost::signals2;
namespace bofs = ::boost::filesystem;
namespace bpot = ::boost::posix_time;
namespace bgre = ::boost::gregorian;
namespace bprt = ::boost::property_tree;
namespace bpop = ::boost::program_options;

bpot::ptime utc_to_local (const bpot::ptime & pt);
bpot::ptime local_to_utc (const bpot::ptime & pt);

#endif // HIPRO_THITTAM__1f1ef54a_c2c2_11e2_ab99_001f3c9e2082

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
