/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__ea8a30f8_00fd_11e9_8822_30e37a0d36da
#define HIPRO__ea8a30f8_00fd_11e9_8822_30e37a0d36da

#include <string>
#include <list>

#include "_namespace.h"
#include "resource.h"

NAMESPACE__THITTAM__START

class ResourceGroup
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

  const Resource & add_resource (void);

private:
  std::string m_id;
  std::string m_name;
  std::list <Resource> m_resources;

  auto get_resource (const std::string & id) const;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__ea8a30f8_00fd_11e9_8822_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
