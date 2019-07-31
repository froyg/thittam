/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include "util.h"

using namespace thittam::util;


TEST (EffortStrToMinutesTest, Year)
{
  std::vector<std::string> years =
    { "y", "yr", "yrs", "year", "years" };
  std::vector<double> numOfYears = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; ++hours)
    for (short weekDays = 1; weekDays <= 7; ++weekDays)
      for (auto &i : numOfYears)
        for (auto &j : years)
          {
            int mins = round(i * 365.25 * hours * 60 * weekDays / 7.0);
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Month)
{
  std::vector<std::string> months =
    {"m", "month", "months", "mth", "mnth", "mnths"};
  std::vector<double> numOfMonths = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; ++hours)
    for (short weekDays = 1; weekDays <= 7; ++weekDays)
      for (auto &i : numOfMonths)
        for (auto &j : months)
          {
            int mins = round(i * hours * 60 * (4 * weekDays + 2));
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Week)
{
  std::vector<std::string> week =
    {"w", "week", "weeks", "wk", "wks", "wek", "weks"};
  std::vector<double> numOfWeeks = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; ++hours)
    for (short weekDays = 1; weekDays <= 7; ++weekDays)
      for (auto &i : numOfWeeks)
        for (auto &j : week)
          {
            int mins = round(i * weekDays * hours * 60);
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Day)
{
  std::vector<std::string> day =
    {"d", "ds", "day", "days", "da", "das", "dy", "dys"};
  std::vector<double> numOfDays = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; ++hours)
    for (short weekDays = 1; weekDays <= 7; weekDays += 3)
      for (auto &i : numOfDays)
        for (auto &j : day)
          {
            int mins = round(i * hours * 60);
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Hour)
{
  std::vector<std::string> hour =
    {"h", "hr", "hrs", "hour", "hours"};
  std::vector<double> numOfHours = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; hours += 3)
    for (short weekDays = 1; weekDays <= 7; weekDays += 3)
      for (auto &i : numOfHours)
        for (auto &j : hour)
          {
            int mins = round(i * 60);
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Minute)
{
  std::vector<std::string> minute =
    {"mn", "mns", "min", "mins", "minute", "minutes"};
  std::vector<double> numOfMinutes = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; hours += 3)
    for (short weekDays = 1; weekDays <= 7; weekDays += 3)
      for (auto &i : numOfMinutes)
        for (auto &j : minute)
          {
            int mins = round(i);
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Second)
{
  std::vector<std::string> second =
    {"s", "sec", "secs", "second", "seconds"};
  std::vector<double> numOfSeconds = {0.1, 0.25, 1.26, 1, 2, 3, 13.05};
  for (short hours = 1; hours <= 24; hours += 3)
    for (short weekDays = 1; weekDays <= 7; weekDays += 3)
      for (auto &i : numOfSeconds)
        for (auto &j : second)
          {
            int mins = round(i / 60.0);
            std::string effort = boost::lexical_cast<std::string>(i) + "  " + j;
            int returnValue = effort_str_to_minutes(effort, weekDays, hours);
            ASSERT_EQ(returnValue, mins);
          }
}

TEST (EffortStrToMinutesTest, Mixed)
{
  std::string effort[] =
    {
     "1d 2w 3h", "3hr 4weeks", "2.5 weeks 9 hrs", "5ds 6 hours", "32 wks 4days",
     "1mins 30 secs", "3 month 9days", "3.5 years 10 days", "3d 4hrs 2 mins"
    };
  int minutes[] = {21780, 40500, 25740, 7560, 328320, 2, 142560, 1855260, 4562};
  short hours = 24;
  short weekDays = 7;
  for (unsigned i = 0; i < sizeof(minutes)/sizeof(int); ++i)
  {
    int returnValue = effort_str_to_minutes(effort[i], weekDays, hours);
    ASSERT_EQ(returnValue, minutes[i]);
  }
}


/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
