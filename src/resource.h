/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c
#define HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

#include <string>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class Resource
{
public:
  const std::string & resource_id (void) const
  {
    return m_id;
  }

  const std::string & resource_name (void) const
  {
    return m_name;
  }

  const float & resource_cost (void) const
  {
    return m_cost;
  }

  void set_resource_id (const std::string & id)
  {
    m_id = id;
  }
  
  void set_resource_name (const std::string & name)
  {
    m_name = name;
  }

  void set_resource_cost (const float & cost)
  {
    m_cost = cost;
  }

private:
  std::string m_id;
  std::string m_name;
  float m_cost;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
