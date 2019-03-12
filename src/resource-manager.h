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
  bool
  add_group(ResourceGroup& group_name);

  const Resource*
  get_resource(const std::string& group_id,
    const std::string& resource_id) const;
  Resource*
  get_resource_mutable(const std::string& group_id,
    const std::string& resource_id);
  const ResourceGroup*
  get_resource_group(const std::string& id) const;
  ResourceGroup*
  get_resource_group_mutable(const std::string& id);
  bool
  is_unique_group_name(const std::string& group_name) const;

  // WIP
  void
  generate_json(void);

private:
  static unsigned int m_id_counter;
  std::list <ResourceGroup> m_resource_groups;

  void
  create_group_id(void);
  void
  renumber_ids(void);
};

NAMESPACE__THITTAM__END

#endif // HIPRO__8aa70514_0100_11e9_b81a_30e37a0d36da

/*
  Local Variables:
  mode: c++
  End:
*/
