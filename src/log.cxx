/* Copyright (C) 2008-2017 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <cstdarg>
#include <cstdio>

#include <iomanip>
#include <iostream>
#include <type_traits>

#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/value_extraction.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "log.h"

NAMESPACE__HIPRO_LOG__START

void
format_string(char* buffer, size_t len, const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  _Pragma("GCC diagnostic push")
  _Pragma("GCC diagnostic ignored \"-Wformat-security\"")
  vsnprintf(buffer, len, fmt, ap);
  _Pragma("GCC diagnostic pop")
  va_end(ap);
}

static void
formatter(boost::log::record_view const& rec,
  boost::log::formatting_ostream& strm)
{
  auto date_time_formatter =
    boost::log::expressions::format_date_time<boost::posix_time::ptime>(
      "TimeStamp", "%Y-%m-%d %H:%M:%S.%f");

  strm << date_time_formatter(rec, strm) << "|";

  {
    /* Extract severity */
    static const char* strings[] = {
      "TRC",
      "D05",
      "D04",
      "D03",
      "D02",
      "D01",
      "DBG",
      "INF",
      "WRN",
      "ERR",
      "FTL"
    };
    static_assert(((sizeof(strings) / sizeof(char*)) == MAX_LEVEL),
      "Not enough format strings");

    auto val = boost::log::extract<int> ("Severity", rec);
    if (val) {
      auto level = val.get<int> ();
      if ((level >= MIN_LEVEL) && (level <= MAX_LEVEL)) {
        level = level - 1;
        strm << strings[level];
      } else {
        strm << static_cast<int>(level);
      }
    }
  }

  strm << "| " << std::setfill(' ') << std::setw(20);

  {
    /* Extract filename attribute and left trim to 20 characters */
    const int len = 20;
    auto val = boost::log::extract<std::string> ("File", rec);
    if (val) {
      auto filename = val.get<std::string> ();
      if (filename.length() > len) {
        strm << filename.substr((filename.length() - len), len);
      } else {
        strm << filename;
      }
    }
  }

  strm << std::setfill(' ') << ":" << std::setfill('0') << std::setw(4);
  {
    /* Extract Line number attribute */
    auto val = boost::log::extract<int> ("Line", rec);
    if (val) {
      auto line = val.get<int> ();
      strm << line;
    }
  }

  strm << "| " << std::setfill(' ') << std::setw(5);

  {
    /* Extract channel name attribute and left trim to 5 characters */
    const int len = 5;
    auto val = boost::log::extract<std::string> ("Channel", rec);
    if (val) {
      auto channel = val.get<std::string> ();
      if (channel.length() > len) {
        strm << channel.substr((channel.length() - len), len);
      } else {
        strm << channel;
      }
    }
  }

  strm << "| " << rec[boost::log::expressions::smessage];
}

Logger*
LoggerManager::get(const std::string& name)
{
  auto search = m_cache.find(name);
  if (search != m_cache.end()) {
    return search->second.get();
  }

  auto logger = std::make_unique<Logger> (boost::log::keywords::channel = name);
  auto logger_ptr = logger.get();
  m_cache[name] = std::move(logger);
  return logger_ptr;
}

void
setup_console_logging(void)
{
  auto lg = boost::log::core::get();
  auto sink = boost::log::add_console_log();
  sink->set_formatter(&formatter);
  lg->add_sink(sink);
  boost::log::add_common_attributes();
}

void
setup_file_logging(const std::string& filename)
{
  auto lg = boost::log::core::get();
  auto sink = boost::log::add_file_log(
      boost::log::keywords::file_name = filename,
      boost::log::keywords::auto_flush = true,
      boost::log::keywords::open_mode = (std::ios_base::out | std::ios_base::app)
    );
  sink->set_formatter(&formatter);
  lg->add_sink(sink);
  boost::log::add_common_attributes();
}

void
set_logging_severity(int log_level)
{
  auto lg = boost::log::core::get();
  lg->set_filter(boost::log::expressions::attr<int>("Severity") >= log_level);
}

NAMESPACE__HIPRO_LOG__END

/*
  Local Variables:
  mode: c++
  End:
*/
