/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__78fe21a0_fd94_11e2_852c_001f3c9e2082
#define HIPRO_THITTAM__78fe21a0_fd94_11e2_852c_001f3c9e2082

#include <string>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

#include "common.h"
#include "config.h"
#include "log.h"

class FileConfigSource : public ConfigSource
{
public:
  FileConfigSource (hipro::log::Logger* logger,
                    const bofs::path & config_file);
  ~FileConfigSource () {}

  /*--- ConfigSource interface ---*/
  const std::string & read (void);
  void write (const std::string & data);

private:
  hipro::log::Logger* logger;
  const bofs::path m_config_file;
  std::string m_data;
};

class PersistentConfig : public Config
{
public:
  PersistentConfig (hipro::log::Logger* logger,
                    std::unique_ptr<ConfigSource> && config_source);
  ~PersistentConfig () {}

  /*--- Config interface ---*/
  void set_server_address (const std::string & server_address);
  const std::string & server_address (void) const
  {
    return m_server_address;
  }
  void operator= (const Config & other);

private:
  void save (void);

private:
  hipro::log::Logger* logger;
  std::unique_ptr<ConfigSource> m_config_source;

  std::string m_server_address;
};


class InMemoryConfig : public Config
{
public:
  InMemoryConfig (hipro::log::Logger* logger)
    : logger (logger) {}
  ~InMemoryConfig () {}

  /*--- Config interface ---*/
  void set_server_address (const std::string & server_address)
  {
    m_server_address = server_address;
  }

  const std::string & server_address (void) const
  {
    return m_server_address;
  }

  void operator= (const Config & other)
  {
    m_server_address = other.server_address ();
  }

private:
  hipro::log::Logger* logger;
  std::string m_server_address;
};

#endif // HIPRO_THITTAM__78fe21a0_fd94_11e2_852c_001f3c9e2082

/*
  Local Variables:
  mode: c++
  End:
*/
