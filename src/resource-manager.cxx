/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <fstream>

#include "resource-manager.h"

NAMESPACE__THITTAM__START

unsigned int ResourceManager::m_id_counter = 0;

const Resource*
ResourceManager::get_resource ( const std::string& group_id, const std::string& resource_id ) const
{
  return get_resource_group ( group_id )->ResourceGroup::get_resource ( resource_id );
}

Resource*
ResourceManager::get_resource_mutable ( const std::string& group_id, const std::string& resource_id )
{
  return get_resource_group_mutable ( group_id )->ResourceGroup::get_resource_mutable ( resource_id );
}

const ResourceGroup*
ResourceManager::get_resource_group ( const std::string& id ) const
{
  for ( auto& it : m_resource_groups )
    {
      if ( it.id() == id )
        {
          return &it;
        }
    }
  return NULL;
}

ResourceGroup*
ResourceManager::get_resource_group_mutable ( const std::string& id )
{
  for ( auto& it : m_resource_groups )
    {
      if ( it.id() == id )
        {
          return &it;
        }
    }
  return NULL;
}

void
ResourceManager::renumber_ids ( void )
{
  for ( auto& it : m_resource_groups )
    {
      m_id_counter++;
      it.set_id ( std::to_string ( m_id_counter ) );
    }
}

void
ResourceManager::create_group_id ( void )
{
  if ( m_id_counter - m_resource_groups.size() > SIZE_COUNTER_DIFFERENCE )
    {
      renumber_ids();
    }
  m_id_counter++;
}

bool
ResourceManager::is_unique_group_name ( const std::string& group_name )
{
  for ( auto& it : m_resource_groups )
    {
      if ( it.name() == group_name )
        {
          return false;
        }
    }
  return true;
}

bool
ResourceManager::add_group ( ResourceGroup& group )
{
  if ( !is_unique_group_name ( group.name() ) )
    {
      return false;
    }

  create_group_id();
  group.set_id ( std::to_string ( m_id_counter ) );
  m_resource_groups.push_back ( group );
  return true;
}

void
ResourceManager::generate_json ( void )
{
  // WIP
  std::ofstream outFile;
  outFile.open ( "new.json" );

  for ( auto& it : m_resource_groups )
    {
      outFile << it.ResourceGroup::id() << "\n";
      outFile << it.ResourceGroup::name() << "\n";
    }
  outFile.close();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
