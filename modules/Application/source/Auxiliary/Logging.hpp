#ifndef Geo_Application_Auxiliary_LoggingMacros
#define Geo_Application_Auxiliary_LoggingMacros

#include <Uni/Logging/LogRecordStreamer>
#include <Uni/Logging/SimpleLogger>

#include <string.h>

static Uni::Logging::SimpleLogger
  Geo_Application_simple_logger_("Application");

#define Geo_Application_LOG_STREAM(              \
    logger, severity, file_path, line_number) \
  Uni_Logging_LOG_STREAM(                     \
    Uni::Logging::SimpleLogger,               \
    logger, severity, file_path, line_number) \

#define Geo_Application_LOG_LOCATION \
  __FILE__

#define DEBUG                    \
  Geo_Application_LOG_STREAM(       \
    Geo_Application_simple_logger_, \
    1, Geo_Application_LOG_LOCATION, __LINE__)

#define INFO                     \
  Geo_Application_LOG_STREAM(       \
    Geo_Application_simple_logger_, \
    2, Geo_Application_LOG_LOCATION, __LINE__)

#define WARNING                  \
  Geo_Application_LOG_STREAM(       \
    Geo_Application_simple_logger_, \
    3, Geo_Application_LOG_LOCATION, __LINE__)

#define ERROR                    \
  Geo_Application_LOG_STREAM(       \
    Geo_Application_simple_logger_, \
    4, Geo_Application_LOG_LOCATION, __LINE__)

#define FATAL                    \
  Geo_Application_LOG_STREAM(       \
    Geo_Application_simple_logger_, \
    5, Geo_Application_LOG_LOCATION, __LINE__)

#endif
// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
