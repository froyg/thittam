/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__b118fb6a_00fd_11e9_ae49_30e37a0d36da
#define HIPRO__b118fb6a_00fd_11e9_ae49_30e37a0d36da

#include <string>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class Resource
{
public:
  const std::string & id (void) const
  {
    return m_id;
  }

  const std::string & name (void) const
  {
    return m_name;
  }

  const float & cost (void) const
  {
    return m_cost;
  }

  void set_id (const std::string & id)
  {
    if (id.length() <= 6){
      m_id = id;
    }
  }

  void set_name (const std::string & name)
  {
    m_name = name;
  }

  void set_cost (const float & cost)
  {
    m_cost = cost;
  }

private:
  std::string m_id;
  std::string m_name;
  float m_cost;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__b118fb6a_00fd_11e9_ae49_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
