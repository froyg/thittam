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


class FileConfigSource : public ConfigSource
{
public:
  typedef ::std::shared_ptr<FileConfigSource> ptr_t;

public:
  /*--- ctor/dtor/factory ---*/
  static ptr_t create (HLogPtr & logger,
                       const bofs::path & config_file)
  {
    ptr_t object (new FileConfigSource (logger, config_file));
    return object;
  }

  FileConfigSource (HLogPtr & logger,
                    const bofs::path & config_file);
  ~FileConfigSource () {}

  /*--- Methods required by the ConfigSource interface ---*/
  const std::string & read (void);
  void write (const std::string & data);

  /*--- Data members ---*/
  HLogPtr m_logger;
  const bofs::path m_config_file;
  std::string m_data;
};


class PersistentConfig : public Config
{
public:
  typedef ::std::shared_ptr<PersistentConfig> ptr_t;

public:
  /*--- ctor/dtor/factory ---*/
  static ptr_t create (HLogPtr & logger,
                       ConfigSource::ptr_t & config_source)
  {
    ptr_t object (new PersistentConfig (logger, config_source));
    return object;
  }

  PersistentConfig (HLogPtr & logger,
                    ConfigSource::ptr_t & config_source);
  ~PersistentConfig () {}

  /*--- Methods required by the Config interface ---*/
  void set_server_address (const std::string & server_address);
  const std::string & server_address (void) { return m_server_address; }
  void operator= (const Config::ptr_t & other);

  /*--- Other convenience methods ---*/
  void save (void);

  /*--- Data members ---*/
  HLogPtr m_logger;
  ConfigSource::ptr_t m_config_source;

  std::string m_server_address;
};


class InMemoryConfig : public Config
{
public:
  typedef ::std::shared_ptr<InMemoryConfig> ptr_t;

public:
  /*--- ctor/dtor/factory ---*/
  static ptr_t create (HLogPtr logger)
  {
    ptr_t object (new InMemoryConfig (logger));
    return object;
  }

  InMemoryConfig (HLogPtr logger)
    : m_logger (logger) {}
  ~InMemoryConfig () {}

  /*--- Methods required by the Config interface ---*/
  void set_server_address (const std::string & server_address)
  {
    m_server_address = server_address;
  }

  const std::string & server_address (void)
  {
    return m_server_address;
  }

  void operator= (const Config::ptr_t & other)
  {
    set_server_address (other->server_address ());
  }

  /*--- Data members ---*/
  HLogPtr m_logger;
  std::string m_server_address;
};

#endif // HIPRO_THITTAM__78fe21a0_fd94_11e2_852c_001f3c9e2082

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
