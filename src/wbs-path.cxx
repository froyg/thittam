/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "wbs-path.h"

NAMESPACE__THITTAM__START

std::ostream& operator << (std::ostream & os, const WBSPath & path)
{
  const auto & parts = path.parts ();

  auto it = parts.cbegin ();
  while (it != parts.cend ())
  {
    os << *it;
    ++it;
    if (it != parts.cend ())
    {
      os << ".";
    }
  }

  return os;
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
