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

  const std::string & description () const
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

  void set_description (const std::string & description)
  {
    m_description = description;
  }

  bool add_resource (const std::string & resource_name);

  const Resource * get_resource (const std::string& id) const;
  Resource * get_resource_mutable (const std::string& id);

private:
  static unsigned int m_id_counter;
  std::string m_id;
  // Hidden from user. NOTNULL & UNIQUE
  
  std::string m_name;
  // NOTNULL & UNIQUE

  std::string m_description;
  std::list <Resource> m_resources;

  void create_resource_id (void);
  void renumber_ids (void);
  bool is_unique_resource_name (const std::string & resource_name);
};

NAMESPACE__THITTAM__END

#endif // HIPRO__ea8a30f8_00fd_11e9_8822_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
