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
#include <cmath>

#include "_namespace.h"

NAMESPACE__THITTAM__START

#define SIZE_COUNTER_DIFFERENCE 100

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

  const std::string & long_name (void) const
  {
    return m_long_name;
  }

  const float & cost (void) const
  {
    return m_cost;
  }

  const std::string & description (void) const
  {
    return m_description;
  }

  void set_id (const std::string & id)
  {
    m_id = id;
  }

  void set_name (const std::string & name)
  {
    m_name = name;
  }

  void set_long_name (const std::string & long_name)
  {
    m_long_name = long_name;
  }

  void set_cost (const float & cost)
  {
    m_cost = roundf(cost * 100) / 100;
  }

  void set_description (const std::string & description)
  {
    m_description = description;
  }

private:
  std::string m_id;
  // Hidden from user. NOTNULL & UNIQUE
  std::string m_name;
  // NOTNULL & UNIQUE

  std::string m_long_name;
  float m_cost;
  std::string m_description;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__b118fb6a_00fd_11e9_ae49_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
