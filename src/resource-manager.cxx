/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "resource-manager.h"

NAMESPACE__THITTAM__START

unsigned int ResourceManager::m_id_counter = 0;

const Resource*
ResourceManager::get_resource(const std::string& group_id,
  const std::string& resource_id) const
{
  return get_resource_group(group_id)->ResourceGroup::get_resource(resource_id);
}

Resource*
ResourceManager::get_resource_mutable(const std::string& group_id,
  const std::string& resource_id)
{
  return get_resource_group_mutable(
      group_id)->ResourceGroup::get_resource_mutable(resource_id);
}

const ResourceGroup*
ResourceManager::get_resource_group(const std::string& id) const
{
  for (auto& it : m_resource_groups) {
    if (it.id() == id) {
      return &it;
    }
  }
  return NULL;
}

ResourceGroup*
ResourceManager::get_resource_group_mutable(const std::string& id)
{
  for (auto& it : m_resource_groups) {
    if (it.id() == id) {
      return &it;
    }
  }
  return NULL;
}

void
ResourceManager::renumber_ids(void)
{
  for (auto& it : m_resource_groups) {
    m_id_counter++;
    it.set_id(std::to_string(m_id_counter));
  }
}

void
ResourceManager::create_group_id(void)
{
  if (m_id_counter - m_resource_groups.size() > SIZE_COUNTER_DIFFERENCE) {
    renumber_ids();
  }
  m_id_counter++;
}

bool
ResourceManager::is_unique_group_name(const std::string& group_name) const
{
  // Resource Group Name must be unique and not null
  // and must not contain space

  if (group_name.empty()) {
    return false;
  }

  for (size_t i = 0; i < group_name.length(); i++) {
    if(!isalnum(group_name.at(i))) {
      return false;
    }
  }

  for (auto& it : m_resource_groups) {
    if (it.name() == group_name) {
      return false;
    }
  }
  return true;
}

bool
ResourceManager::add_group(ResourceGroup& group)
{
  if (!is_unique_group_name(group.name())) {
    return false;
  }

  create_group_id();
  group.set_id(std::to_string(m_id_counter));
  m_resource_groups.push_back(group);
  return true;
}

bool
ResourceManager::delete_group ( const std::string& group_id )
{
  const auto old_size = m_resource_groups.size();
  m_resource_groups.remove_if (
    [&group_id] ( const auto & rg ) -> bool
  {
    return group_id == rg.id();
  } );
  return ( old_size - m_resource_groups.size() > 0 );
}

// returns a resource's parent resource group
ResourceGroup*
ResourceManager::get_parent_mutable (const std::string& resource_id)
{
	for(auto& it : m_resource_groups) {
		if(get_resource(it.id(), resource_id) != NULL) {
			return &it;
		}
	}
	return NULL;
}

bool
ResourceManager::modify_organisation (std::vector<std::string> ids, 
	const std::string& id)
{
	// if `selection` is group and `buffer` is resource
	// paste resources in that group

	for(unsigned int i = 0; i < ids.size(); i++) {
		auto selection = get_resource_group_mutable(id);
		if(!selection) {
			return false;
		}

		auto parent = get_parent_mutable(ids[i]);
		if(!parent) {
			return false;
		}

		auto res = get_resource_mutable(parent->id(), ids[i]);
		if(!res) {
			return false;
		}

		// create copy of resource
		Resource new_res;
		new_res.set_id(res->id());
		new_res.set_name(res->name());
		new_res.set_long_name(res->long_name());
		new_res.set_cost(res->cost());
		new_res.set_description(res->description());

		// delete this resource first, so that
		// id and name remain unique and can be reused
		if(!parent->delete_resource(res->id())) {
			return false;
		}

		// give this resource to ResourceGroup::add_resource()
		if(!selection->add_resource(new_res)) {
			return false;
		}
	}
	return true;

// TODO
	// if selection is `resource` and `buffer` is group
		// do nothing

	// if `selection` is resource and `buffer` is resource
		// paste resources after that res

	// if `selection` is group and `buffer` is group
		// paste groups after that group
}

void
ResourceManager::generate_json(void)
{
  // WIP
  // std::ofstream outFile;
  // outFile.open ( "new.json" );

  // for ( auto& it : m_resource_groups )
  //   {
  //     outFile << it.ResourceGroup::id() << "\n";
  //     outFile << it.ResourceGroup::name() << "\n";
  //   }
  // outFile.close();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
