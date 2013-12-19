#ifndef Geo_LogViewer_Auxiliary_Exception
#define Geo_LogViewer_Auxiliary_Exception

#include <Uni/Logging/LogRecordStreamer>
#include <Uni/Logging/SimpleLogger>

#include <exception>

inline void
throwException() {
  throw
    std::
    exception();
}

#define Geo_LogViewer_Auxiliary_EXCEPTION_STREAM(         \
    Logger, logger, severity, file_path, line_number)     \
  for (Uni::Logging::LogRecordStreamer<Logger>            \
       Geo_LogViewer_Auxiliary_stream_(logger,            \
                                       severity,          \
                                       file_path,         \
                                       line_number);      \
       Geo_LogViewer_Auxiliary_stream_; throwException()) \
    Geo_LogViewer_Auxiliary_stream_

#define EXCEPTION                           \
  Geo_LogViewer_Auxiliary_EXCEPTION_STREAM( \
    Uni::Logging::SimpleLogger,             \
    Geo_LogViewer_Auxiliary_simple_logger_, \
    5, __FILE__, __LINE__)

#endif
// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
