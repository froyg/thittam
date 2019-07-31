/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "util.h"

#include <vector>
#include <cctype>
#include <cmath>

NAMESPACE__THITTAM_UTIL__START


std::string get_string(const std::string &s, unsigned &pos)
{
  std::string returnValue = "";
  while (isalpha(s[pos]))
    {
      returnValue += tolower(s[pos]);
      pos++;
    }
  pos--;
  return returnValue;
}


double get_number(const std::string &s, unsigned &pos) {
  double x = 0.0;
  bool sign = 0;

  if (s[pos] == '-' || s[pos] == '+')
    {
      sign = (s[pos] == '-');
      pos++;
    }

  while (isdigit(s[pos]))
    {
      // Convert the integers first
      x = x * 10 + s[pos] - '0';
      pos++;
    }
  if (s[pos] == '.')
    {
      // Then the fraction
      pos++;
      int negPow = 0;
      while (isdigit(s[pos]))
        {
          if (negPow > -6)
            {
              // Don’t get further than 6 precision
              x = x + (s[pos] - '0') * pow(10, --negPow);
            }
          pos++;
        }
    }
  x = round(x * 1e4) / 1e4;   // 4 digits of significance after decimal point
  pos--;
  return sign ? -x : x;
}


int parse(const std::string &s) {
  if (s == "y" || s == "yr" || s == "yrs" || s == "year" || s == "years")
    {
      return 'y';  // <-------------year
    }

  if (s == "m"    || s == "month" || s == "months" || s == "mth" ||
      s == "mths" || s == "mnth"  || s == "mnths")
    {
      return 'M';  // <-------------month
    }

  if (s == "w" || s == "wk" || s == "wks" || s == "wek" || s == "weks" ||
      s == "week" || s == "weeks")
    {
      return 'w';  // <-------------week
    }

  if (s == "d"   || s == "da" || s == "das" || s == "dy" || s == "dys" ||
      s == "day" || s == "days" || s == "ds")
    {
      return 'd';  // <-------------day
    }

  if (s == "h" || s == "hr" || s == "hrs" || s == "hour" || s == "hours")
    {
      return 'h';  // <-------------hour
    }

  if (s == "mn" || s == "mns" || s == "min" || s == "mins" ||
      s == "minute" || s == "minutes")
    {
      return 'm';  // <-------------minute
    }

  if (s == "s" || s == "sec" || s == "secs" || s == "seconds" || s == "second")
    {
      return 's';  // <-------------second
    }

  return 0;
}


// This function returns the minutes given the effort like "1d 3.5h". It throws
// error only when days_per_week or hours_per_day is an invalid number.
int effort_str_to_minutes (const std::string & effort,
                           int days_per_week,
                           int hours_per_day)
{

  double minutes = 0;

  double currentNumber = 0;
  std::string currentString = "";

  for (unsigned i = 0; i < effort.length(); ++i)
    {

      if (/* Fraction or */(effort[i] == '.' && isdigit(effort[i + 1])) ||
          /* Real number */isdigit(effort[i]))
        {
          currentNumber = get_number(effort, i);
        }

      else if (isalpha(effort[i]))
        {
          currentString = std::move(get_string(effort, i));
          if (currentNumber != 0.0) {
            switch (parse(currentString)) {
            case 'y':  // year
              minutes += currentNumber * 365.25 * hours_per_day * 60.0
                * days_per_week / 7.0;
              break;
            case 'M':  // month
              minutes += 120.0 * hours_per_day * currentNumber
                * (2.0 * days_per_week + 1.0);
              break;
            case 'w':  // week
              minutes += 60.0 * hours_per_day * days_per_week * currentNumber;
              break;
            case 'd':  // day
              minutes += 60.0 * hours_per_day * currentNumber;
              break;
            case 'h':
              minutes += 60.0 * currentNumber;
              break;
            case 'm':
              minutes += currentNumber;
              break;
            case 's':
              minutes += currentNumber / 60.0;
              break;
            }
          }
          currentNumber = 0.0;
        }
    }
  return round(minutes);
}

NAMESPACE__THITTAM_UTIL__END

/*
  Local Variables:
  mode: c++
  End:
*/
