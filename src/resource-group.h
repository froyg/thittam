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
#include <vector>
#include <memory>

#include "_namespace.h"
#include "resource.h"

NAMESPACE__THITTAM__START

class ResourceGroup
{
public:
  const std::string & resource_group_id (void) const
  {
    return m_id;
  }

  const std::string & resource_group_name (void) const
  {
    return m_name;
  }

  void set_resource_group_id (const std::string & id)
  {
    m_id = id;
  }
  
  void set_resource_group_name (const std::string & name)
  {
    m_name = name;
  }

  auto get_resource (const std::string & id);
  const std::string & get_resource_name (const std::string & id) const;
  void add_resource (const std::string & id, const std::string & name, const float cost);
  void remove_resource (const std::string & id);

private:
  std::string m_id;
  std::string m_name;
  std::vector <std::unique_ptr<Resource>> m_resources;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__4f14b450_242f_11e8_85b8_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
