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
#include "util.h"

#define FAILED_TO_GENERATE_RANDOM_ID "FAILED"

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
    if (id.length() <= 6) {
      m_id = id;
    }
  }

  void set_name (const std::string & name)
  {
    m_name = name;
  }

  size_t add_resource (void);

  bool change_resource_id (const int index, const std::string & resource_id);
  void change_resource_name (const int index, const std::string & resource_name);
  void change_resource_cost (const int index, const float & resource_cost);

  const Resource & get_resource (const int index) const;

private:
  std::string m_id;
  std::string m_name = "group name";
  std::list <Resource> m_resources;

  Resource & _get_resource (const int index);
  bool validate_resources_id (const std::string & resource_id);
  std::string generate_unique_resource_id (void);
};

NAMESPACE__THITTAM__END

#endif // HIPRO__ea8a30f8_00fd_11e9_8822_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
