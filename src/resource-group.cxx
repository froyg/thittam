/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <iostream>

#include "resource-group.h"

NAMESPACE__THITTAM__START

unsigned int ResourceGroup::m_id_counter = 0;

const Resource*
ResourceGroup::get_resource ( const std::string& id ) const
{
  for ( auto& it : m_resources )
    {
      if ( it.id() == id )
        {
          return &it;
        }
    }
  return NULL;
}

Resource*
ResourceGroup::get_resource_mutable ( const std::string& id )
{
  for ( auto& it : m_resources )
    {
      if ( it.id() == id )
        {
          return &it;
        }
    }
  return NULL;
}

void
ResourceGroup::renumber_ids ( void )
{
  for ( auto& it : m_resources )
    {
      m_id_counter++;
      it.set_id ( std::to_string ( m_id_counter ) );
    }
}

void
ResourceGroup::create_resource_id ( void )
{
  if ( m_id_counter - m_resources.size() > SIZE_COUNTER_DIFFERENCE )
    {
      renumber_ids();
    }
  m_id_counter++;
}

bool
ResourceGroup::is_unique_resource_name ( const std::string& resource_name )
{
  // Resource Name must be unique and not null
  // and must not contain space

  if (resource_name.empty()) {
    return false;
  }

  for (size_t i = 0; i < resource_name.length(); i++) {
    if(!isalnum(resource_name.at(i))) {
      return false;
    }
  }

  for ( auto& it : m_resources ) {
    if ( it.name() == resource_name ) {
      return false;
    }
  }
  return true;
}

bool
ResourceGroup::add_resource ( Resource& resource )
{
  if ( !is_unique_resource_name ( resource.name() ) )
    {
      return false;
    }

  create_resource_id();
  resource.set_id ( std::to_string ( m_id_counter ) );
  m_resources.push_back ( resource );
  return true;
}

bool
ResourceGroup::delete_resource ( const std::string& resource_id )
{
  const auto old_size = m_resources.size();
  m_resources.remove_if (
    [&resource_id] ( const auto & rg ) -> bool
  {
    return resource_id == rg.id();
  } );
  return ( old_size - m_resources.size() > 0 );
}

bool ResourceGroup::delete_resources(const std::vector<std::string> &resource_ids)
{
  auto j = m_resources.begin();
  for (const auto i : resource_ids)
  {
    while (j->id() != i)
    {
      j++;
    }
    m_resources.erase(j);
    j--;
  }
  return true;
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
