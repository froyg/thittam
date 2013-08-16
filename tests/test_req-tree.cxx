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

#include <hdb/log.h>

#include "req-tree_impl.h"
#include "requirement_impl.h"

class ReqTreeTest : public ::testing::Test
{
protected:
  void SetUp (void)
  {
    m_logger = HLog::get ("thittam.tests");
    m_logger->set_level (HLogLevel::WARNING);

    m_req_factory = std::make_shared<RequirementFactoryImpl> (m_logger);
    m_req_tree = std::make_shared<ReqTreeImpl> (m_logger, m_req_factory);
  }

  void TearDown (void)
  {

  }

  HLogPtr m_logger;
  std::shared_ptr<RequirementFactory> m_req_factory;
  std::shared_ptr<ReqTree> m_req_tree;
};

TEST_F (ReqTreeTest, SimpleChildAddToRoot)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  EXPECT_EQ (m_req_tree->get ("1"), req1);
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
