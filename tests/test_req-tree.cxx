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

TEST_F (ReqTreeTest, FirstChild)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  auto req2 = m_req_factory->create ("2", "2", "2");
  m_req_tree->add_child (req1, req2);
  EXPECT_TRUE (m_req_tree->is_first_child (req1));
  EXPECT_TRUE (m_req_tree->is_first_child (req2));
}

TEST_F (ReqTreeTest, LastChild)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  auto req2 = m_req_factory->create ("2", "2", "2");
  m_req_tree->add_child (req1, req2);
  EXPECT_TRUE (m_req_tree->is_last_child (req1));
  EXPECT_TRUE (m_req_tree->is_last_child (req2));
}

TEST_F (ReqTreeTest, TopLevel)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  auto req2 = m_req_factory->create ("2", "2", "2");
  m_req_tree->add_child (req1, req2);
  EXPECT_TRUE (m_req_tree->is_top_level (req1));
  EXPECT_FALSE (m_req_tree->is_top_level (req2));
}

TEST_F (ReqTreeTest, Siblings)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  auto req2 = m_req_factory->create ("2", "2", "2");
  m_req_tree->add_sibling (req1, req2);
  auto req3 = m_req_factory->create ("2.1", "2.1", "2.1");
  m_req_tree->add_child (req2, req3);
  auto req4 = m_req_factory->create ("2.2", "2.2", "2.2");
  m_req_tree->add_child (req2, req4);
  EXPECT_TRUE (m_req_tree->is_first_child (req1));
  EXPECT_TRUE (m_req_tree->is_last_child (req2));
  EXPECT_TRUE (m_req_tree->is_first_child (req3));
  EXPECT_TRUE (m_req_tree->is_last_child (req4));
}

TEST_F (ReqTreeTest, UpChild)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  auto req2 = m_req_factory->create ("2", "2", "2");
  m_req_tree->add_sibling (req1, req2);
  auto req3 = m_req_factory->create ("2.1", "2.1", "2.1");
  m_req_tree->add_child (req2, req3);
  auto req4 = m_req_factory->create ("2.2", "2.2", "2.2");
  m_req_tree->add_child (req2, req4);
  m_req_tree->up_child (req4);
  EXPECT_TRUE (m_req_tree->is_first_child (req4));
  auto req5 = m_req_factory->create ("3", "3", "3");
  m_req_tree->add_child (nullptr, req5);
  EXPECT_TRUE (m_req_tree->is_last_child (req5));
  m_req_tree->up_child (req5);
  EXPECT_FALSE (m_req_tree->is_last_child (req5));
}

TEST_F (ReqTreeTest, DownChild)
{
  auto req1 = m_req_factory->create ("1", "1", "1");
  m_req_tree->add_child (nullptr, req1);
  auto req2 = m_req_factory->create ("2", "2", "2");
  m_req_tree->add_sibling (req1, req2);
  auto req5 = m_req_factory->create ("3", "3", "3");
  m_req_tree->add_child (nullptr, req5);
  auto req3 = m_req_factory->create ("2.1", "2.1", "2.1");
  m_req_tree->add_child (req2, req3);
  auto req4 = m_req_factory->create ("2.2", "2.2", "2.2");
  m_req_tree->add_child (req2, req4);
  m_req_tree->down_child (req3);
  EXPECT_TRUE (m_req_tree->is_last_child (req3));
  EXPECT_TRUE (m_req_tree->is_last_child (req5));
  m_req_tree->down_child (req2);
  EXPECT_FALSE (m_req_tree->is_last_child (req5));
  EXPECT_TRUE (m_req_tree->is_last_child (req2));
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
