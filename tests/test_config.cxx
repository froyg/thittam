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
#include <string>

#include <gtest/gtest.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

#include <hdb/log.h>

#include "config_impl.h"


class ConfigTest : public ::testing::Test
{
protected:
  void
  SetUp(void)
  {
    m_logger = HLog::get("thittam.tests");
    m_logger->set_level(HLogLevel::WARNING);
  }

  void
  TearDown(void)
  {

  }

  HLogPtr m_logger;
};

class MockConfigSource1 : public ConfigSource
{
public:
  typedef ::boost::shared_ptr<MockConfigSource1> ptr_t;

  MockConfigSource1() {}

  const std::string&
  read(void)
  {
    return m_data;
  }
  void
  write(const std::string& data)
  {
    m_data = data;
  }

  const std::string&
  data(void)
  {
    return m_data;
  }

private:
  std::string m_data;
};


TEST_F(ConfigTest, EmptyConfiguration)
{
  ConfigSource::ptr_t cs(new MockConfigSource1());
  PersistentConfig::ptr_t cfg(new PersistentConfig(m_logger, cs));

  EXPECT_EQ(cfg->server_address(), "");
}

TEST_F(ConfigTest, NewSettingInEmptyConfiguration)
{
  ConfigSource::ptr_t cs(new MockConfigSource1());
  PersistentConfig::ptr_t cfg(new PersistentConfig(m_logger, cs));

  EXPECT_EQ(cfg->server_address(), "");

  bprt::ptree pt;
  cfg->set_server_address("test");
  std::istringstream is1(cs->read());
  bprt::read_info(is1, pt);

  EXPECT_EQ(pt.get<std::string> ("basic.server_address", ""), "test");

  std::istringstream is2(cs->read());
  bprt::read_info(is2, pt);

  EXPECT_EQ(pt.get<std::string> ("basic.server_address", ""), "test");
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
