/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__8aa70514_0100_11e9_b81a_30e37a0d36da
#define HIPRO__8aa70514_0100_11e9_b81a_30e37a0d36da

#include <string>
#include <list>

#include "_namespace.h"
#include "resource-group.h"
#include "util.h"

NAMESPACE__THITTAM__START

class ResourceManager
{
public:
  bool change_group_id (const int index, const std::string & group_id);
  void change_group_name (const int index, const std::string & group_name);

  size_t add_group (void);
  size_t add_resource (const int index);

  const std::string & get_group_id (const int) const;
  const std::string & get_group_name (const int) const;

  const std::string & get_resource_id (const int, const int) const;
  const std::string & get_resource_name (const int, const int) const;
  const float get_resource_cost (const int, const int) const;

  bool change_resource_id (const int, const int, const std::string &);
  void change_resource_name (const int, const int, const std::string &);
  void change_resource_cost (const int, const int, const float &);

  const ResourceGroup & get_group (const int index) const;
  const Resource & get_resource (const int, const int) const;

  // WIP
  void generate_json (void);

private:
  std::list <ResourceGroup> m_resource_groups;

  ResourceGroup & _get_group (const std::string & id);
  ResourceGroup & _get_group (const int index);
  bool validate_group_id (const std::string & group_id);
  std::string generate_unique_group_id (void);
};

NAMESPACE__THITTAM__END

#endif // HIPRO__8aa70514_0100_11e9_b81a_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
