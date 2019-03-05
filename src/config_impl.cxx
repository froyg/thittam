/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <iostream>
#include <sstream>
#include <fstream>

#include "config_impl.h"


/*---- class FileConfigSource ----*/

FileConfigSource::FileConfigSource(hipro::log::Logger* logger,
  const bofs::path& config_file)
  : logger(logger),
    m_config_file(config_file)
{
  if (bofs::exists(m_config_file) == false) {
    const bofs::path parent_dir = m_config_file.parent_path();
    if (bofs::is_directory(parent_dir) == false) {
      boost::system::error_code ec;
      bofs::create_directories(parent_dir, ec);
      if (ec) {
        Log_E << "creating directory '" << parent_dir
          << "' threw: " << ec;
        THROW(std::runtime_error, "Failed to create configuration file");
      }
    }
  } else {
    ASSERT((bofs::is_regular_file(m_config_file)),
      "expected regular file at: %s", m_config_file.c_str());
  }
}

const std::string&
FileConfigSource::read(void)
{
  m_data.clear();

  if (bofs::exists(m_config_file)) {
    const std::streamsize max_config_size = 4096;
    char data_buffer [max_config_size];

    std::ifstream ifile;
    ifile.open(m_config_file.c_str());
    ifile.read(data_buffer, max_config_size);

    m_data.copy(data_buffer, ifile.gcount());
  }
  return m_data;
}

void
FileConfigSource::write(const std::string& data)
{
  std::ofstream ofile;
  ofile.open(m_config_file.c_str(), std::ofstream::trunc);
  ofile.write(data.data(), data.size());
}


/*---- class PersistentConfig ----*/

PersistentConfig::PersistentConfig(
  hipro::log::Logger* logger,
  std::unique_ptr<ConfigSource>&& config_source)
  : logger(logger),
    m_config_source(std::move(config_source))
{
  const std::string& config_str = m_config_source->read();
  if (!config_str.empty()) {
    std::istringstream is(config_str);
    bprt::ptree pt;
    bprt::read_info(is, pt);

    m_server_address = pt.get<std::string> ("basic.server_address", "");
  }
}

void
PersistentConfig::set_server_address(const std::string& server_address)
{
  m_server_address = server_address;
  save();
}

void
PersistentConfig::operator= (const Config& other)
{
  m_server_address = other.server_address();
  save();
}

void
PersistentConfig::save(void)
{
  std::ostringstream os;
  bprt::ptree pt;
  pt.put("basic.server_address", m_server_address);
  bprt::write_info(os, pt);

  m_config_source->write(os.str());
}

/*
  Local Variables:
  mode: c++
  End:
*/
