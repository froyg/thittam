/* Copyright (C) 2008-2017 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__4a9e2c78_b513_11e4_8e70_68a3c42125fd
#define HIPRO__4a9e2c78_b513_11e4_8e70_68a3c42125fd

#include <string>
#include <stdexcept>
#include <map>
#include <memory>

#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

#define NAMESPACE__HIPRO_LOG__START namespace hipro { namespace log {
#define NAMESPACE__HIPRO_LOG__END } }

NAMESPACE__HIPRO_LOG__START

typedef boost::log::sources::severity_channel_logger_mt <
int, std::string > Logger;

static constexpr int LEVEL_TRACE = 1;
static constexpr int LEVEL_DEBUG5 = 2;
static constexpr int LEVEL_DEBUG4 = 3;
static constexpr int LEVEL_DEBUG3 = 4;
static constexpr int LEVEL_DEBUG2 = 5;
static constexpr int LEVEL_DEBUG1 = 6;
static constexpr int LEVEL_DEBUG = 7;
static constexpr int LEVEL_INFO = 8;
static constexpr int LEVEL_WARNING = 9;
static constexpr int LEVEL_ERROR = 10;
static constexpr int LEVEL_FATAL = 11;

static constexpr int MIN_LEVEL = 1;
static constexpr int MAX_LEVEL = 11;

class LoggerManager
{
public:
  Logger*
  get(const std::string& name);

private:
  std::map<std::string, std::unique_ptr<Logger>> m_cache;
};

void
format_string(char* buffer, size_t len, const char* fmt, ...);
void
setup_console_logging(void);
void
setup_file_logging(const std::string& filename);
void
set_logging_severity(int level);

NAMESPACE__HIPRO_LOG__END

extern hipro::log::Logger* logger;

#define Log_T BOOST_LOG_SEV(*logger, hipro::log::LEVEL_TRACE) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_D BOOST_LOG_SEV(*logger, hipro::log::LEVEL_DEBUG) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_D1 BOOST_LOG_SEV(*logger, hipro::log::LEVEL_DEBUG1) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_D2 BOOST_LOG_SEV(*logger, hipro::log::LEVEL_DEBUG2) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_D3 BOOST_LOG_SEV(*logger, hipro::log::LEVEL_DEBUG3) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_D4 BOOST_LOG_SEV(*logger, hipro::log::LEVEL_DEBUG4) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_D5 BOOST_LOG_SEV(*logger, hipro::log::LEVEL_DEBUG5) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_I BOOST_LOG_SEV(*logger, hipro::log::LEVEL_INFO) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_W BOOST_LOG_SEV(*logger, hipro::log::LEVEL_WARNING) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_E BOOST_LOG_SEV(*logger, hipro::log::LEVEL_ERROR) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)
#define Log_F BOOST_LOG_SEV(*logger, hipro::log::LEVEL_FATAL) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Line", __LINE__)

/* Below snippet taken from HDB log */

#define THROW(x, fmt, ...) do {                                         \
    const int msg_len = 2048;                                           \
    char msg[msg_len];                                                  \
    hipro::log::format_string (msg, msg_len, fmt, ##__VA_ARGS__);         \
    msg[msg_len - 1] = 0;                                               \
    Log_F << "Exception : " << #x << " (" << msg << ")";                \
    x e(msg);                                                           \
    throw e;                                                            \
  } while(0)

#define ASSERT(x, fmt, ...) do {                                        \
    if (!x)                                                             \
    {                                                                   \
      THROW (std::runtime_error,                                        \
                     "Assertion failed: " #x "\n" fmt, ##__VA_ARGS__);  \
    }                                                                   \
  } while (0)

#endif // HIPRO__4a9e2c78_b513_11e4_8e70_68a3c42125fd

/*
  Local Variables:
  mode: c++
  End:
*/
