//
// Created by Shuhao Zhang on 19/07/2021.
//

#ifndef ADB_INCLUDE_UTILS_LOGGER_HPP_
#define ADB_INCLUDE_UTILS_LOGGER_HPP_
// TRACE < DEBUG < INFO < WARN < ERROR < FATAL

#include <Utils/StacktraceLoader.hpp>
#include <iostream>
#include <log4cxx/consoleappender.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/logger.h>
#include <log4cxx/patternlayout.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

enum DebugLevel {
  LOG_NONE, LOG_WARNING, LOG_DEBUG, LOG_INFO, LOG_TRACE
};

static std::string getDebugLevelAsString(DebugLevel level) {
  if (level == LOG_NONE) {
    return "LOG_NONE";
  } else if (level == LOG_WARNING) {
    return "LOG_WARNING";
  } else if (level == LOG_DEBUG) {
    return "LOG_DEBUG";
  } else if (level == LOG_INFO) {
    return "LOG_INFO";
  } else if (level == LOG_TRACE) {
    return "LOG_TRACE";
  } else {
    return "UNKNOWN";
  }
}
/*
static DebugLevel getStringAsDebugLevel(std::string level) {
  if (level == "LOG_NONE") {
    return LOG_NONE;
  } else if (level == "LOG_WARNING") {
    return LOG_WARNING;
  } else if (level == "LOG_DEBUG") {
    return LOG_DEBUG;
  } else if (level == "LOG_INFO") {
    return LOG_INFO;
  } else if (level == "LOG_TRACE") {
    return LOG_TRACE;
  } else {
    throw std::runtime_error("Logger: Debug level unknown: " + level);
  }
}
*/
static log4cxx::LoggerPtr aliancedbLogger(log4cxx::Logger::getLogger("aliancedb"));

// LoggerPtr logger(Logger::getLogger("aliancedb"));

// TRACE < DEBUG < INFO < WARN < ERROR < FATAL
#define LEVEL_TRACE 6
#define LEVEL_DEBUG 5
#define LEVEL_INFO 4
#define LEVEL_WARN 3
#define LEVEL_ERROR 2
#define LEVEL_FATAL 1

#ifdef ADB_LOGGING_LEVEL
#if ADB_LOGGING_LEVEL >= LEVEL_TRACE
#define ADB_TRACE(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_TRACE(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#else
#define ADB_TRACE(TEXT)                                                                                                          \
    do {                                                                                                                         \
        std::ostringstream oss;                                                                                                  \
        ((void) (oss << TEXT));                                                                                                  \
    } while (0)
#endif

#if ADB_LOGGING_LEVEL >= LEVEL_DEBUG
#define ADB_DEBUG(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_DEBUG(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#else
#define ADB_DEBUG(TEXT)                                                                                                          \
    do {                                                                                                                         \
        std::ostringstream oss;                                                                                                  \
        ((void) (oss << TEXT));                                                                                                  \
    } while (0)
#endif

#if ADB_LOGGING_LEVEL >= LEVEL_INFO
#define ADB_INFO(TEXT)                                                                                                           \
    do {                                                                                                                         \
        LOG4CXX_INFO(aliancedbLogger, TEXT);                                                                                           \
    } while (0)
#else
#define ADB_INFO(TEXT)                                                                                                           \
    do {                                                                                                                         \
        std::ostringstream oss;                                                                                                  \
        ((void) (oss << TEXT));                                                                                                  \
    } while (0)
#endif

#if ADB_LOGGING_LEVEL >= LEVEL_WARN
#define ADB_WARNING(TEXT)                                                                                                        \
    do {                                                                                                                         \
        LOG4CXX_WARN(aliancedbLogger, TEXT);                                                                                           \
    } while (0)
#else
#define ADB_WARNING(TEXT)                                                                                                        \
    do {                                                                                                                         \
        std::ostringstream oss;                                                                                                  \
        ((void) (oss << TEXT));                                                                                                  \
    } while (0)
#endif

#if ADB_LOGGING_LEVEL >= LEVEL_ERROR
#define ADB_ERROR(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_ERROR(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#else
#define ADB_ERROR(TEXT)                                                                                                          \
    do {                                                                                                                         \
        std::ostringstream oss;                                                                                                  \
        ((void) (oss << TEXT));                                                                                                  \
    } while (0)
#endif

#if ADB_LOGGING_LEVEL >= LEVEL_FATAL
#define ADB_FATAL_ERROR(TEXT)                                                                                                    \
    do {                                                                                                                         \
        LOG4CXX_ERROR(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#else
#define ADB_FATAL_ERROR(TEXT)                                                                                                    \
    do {                                                                                                                         \
        std::ostringstream oss;                                                                                                  \
        ((void) (oss << TEXT));                                                                                                  \
    } while (0)
#endif
#else
#define ADB_TRACE(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_TRACE(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#define ADB_DEBUG(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_DEBUG(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#define ADB_TRACE(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_TRACE(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#define ADB_INFO(TEXT)                                                                                                           \
    do {                                                                                                                         \
        LOG4CXX_INFO(aliancedbLogger, TEXT);                                                                                           \
    } while (0)
#define ADB_WARNING(TEXT)                                                                                                        \
    do {                                                                                                                         \
        LOG4CXX_WARN(aliancedbLogger, TEXT);                                                                                           \
    } while (0)
#define ADB_ERROR(TEXT)                                                                                                          \
    do {                                                                                                                         \
        LOG4CXX_ERROR(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#define ADB_FATAL_ERROR(TEXT)                                                                                                    \
    do {                                                                                                                         \
        LOG4CXX_ERROR(aliancedbLogger, TEXT);                                                                                          \
    } while (0)
#endif

#ifdef ADB_DEBUG
#define ADB_VERIFY(CONDITION, TEXT)                                                                                              \
    do {                                                                                                                         \
        if (!(CONDITION)) {                                                                                                      \
            aliancedb::collectAndPrintStacktrace();                                                                                    \
            ADB_FATAL_ERROR(TEXT);                                                                                               \
            throw std::runtime_error("aliancedb Runtime Error on condition " #CONDITION);                                              \
        }                                                                                                                        \
    } while (0)
#else
#define ADB_VERIFY(CONDITION, TEXT) ((void) 0)
#endif

#define ADB_ASSERT(CONDITION, TEXT)                                                                                              \
    do {                                                                                                                         \
        if (!(CONDITION)) {                                                                                                      \
            aliancedb::collectAndPrintStacktrace();                                                                                    \
            ADB_FATAL_ERROR(TEXT);                                                                                               \
            throw std::runtime_error("aliancedb Runtime Error on condition " #CONDITION);                                              \
        }                                                                                                                        \
    } while (0)

#define ADB_ASSERT2(CONDITION, ...)                                                                                              \
    do {                                                                                                                         \
        if (!(CONDITION)) {                                                                                                      \
            aliancedb::collectAndPrintStacktrace();                                                                                    \
            ADB_FATAL_ERROR(__VA_ARGS__);                                                                                        \
            throw std::runtime_error("aliancedb Runtime Error on condition " #CONDITION);                                              \
        }                                                                                                                        \
    } while (0)

#define ADB_THROW_RUNTIME_ERROR(TEXT)                                                                                            \
    do {                                                                                                                         \
        aliancedb::collectAndPrintStacktrace();                                                                                        \
        ADB_FATAL_ERROR(TEXT);                                                                                                   \
        throw std::runtime_error(TEXT);                                                                                          \
    } while (0)

static void setupLogging(std::string logFileName, DebugLevel level) {
  std::cout << "Logger: SETUP_LOGGING" << std::endl;
  // create PatternLayout
  log4cxx::LayoutPtr
      layoutPtr(new log4cxx::PatternLayout("%d{MMM dd yyyy HH:mm:ss} %c: %l %X{threadName} [%-5t] [%p] : %m%n"));

  // create FileAppender
  LOG4CXX_DECODE_CHAR(fileName, logFileName);
  log4cxx::FileAppenderPtr file(new log4cxx::FileAppender(layoutPtr, fileName));

  // create ConsoleAppender
  log4cxx::ConsoleAppenderPtr console(new log4cxx::ConsoleAppender(layoutPtr));

  // set log level
#ifdef ADB_LOGGING_LEVEL
  ((void) level);
#if ADB_LOGGING_LEVEL == LEVEL_FATAL
    aliancedbLogger->setLevel(log4cxx::Level::getFatal());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_ERROR
    aliancedbLogger->setLevel(log4cxx::Level::getError());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_WARN
    aliancedbLogger->setLevel(log4cxx::Level::getWarn());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_INFO
    aliancedbLogger->setLevel(log4cxx::Level::getInfo());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_DEBUG
    aliancedbLogger->setLevel(log4cxx::Level::getDebug());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_TRACE
    aliancedbLogger->setLevel(log4cxx::Level::getTrace());
#endif
#else
  if (level == LOG_NONE) {
    aliancedbLogger->setLevel(log4cxx::Level::getOff());
  } else if (level == LOG_WARNING) {
    aliancedbLogger->setLevel(log4cxx::Level::getWarn());
  } else if (level == LOG_DEBUG) {
    aliancedbLogger->setLevel(log4cxx::Level::getDebug());
  } else if (level == LOG_INFO) {
    aliancedbLogger->setLevel(log4cxx::Level::getInfo());
  } else if (level == LOG_TRACE) {
    aliancedbLogger->setLevel(log4cxx::Level::getTrace());
  } else {
    ADB_ERROR("setupLogging: log level not supported " << getDebugLevelAsString(level));
    throw Exception("Error while setup logging");
  }
#endif

  aliancedbLogger->addAppender(file);
  aliancedbLogger->addAppender(console);
}
/*
static void setLogLevel(DebugLevel level) {
  // set log level
#ifdef ADB_LOGGING_LEVEL
  ((void) level);
#if ADB_LOGGING_LEVEL == LEVEL_FATAL
    aliancedbLogger->setLevel(log4cxx::Level::getFatal());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_ERROR
    aliancedbLogger->setLevel(log4cxx::Level::getError());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_WARN
    aliancedbLogger->setLevel(log4cxx::Level::getWarn());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_INFO
    aliancedbLogger->setLevel(log4cxx::Level::getInfo());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_DEBUG
    aliancedbLogger->setLevel(log4cxx::Level::getDebug());
#endif
#if ADB_LOGGING_LEVEL == LEVEL_TRACE
    aliancedbLogger->setLevel(log4cxx::Level::getTrace());
#endif
#else
  if (level == LOG_NONE) {
    aliancedbLogger->setLevel(log4cxx::Level::getOff());
  } else if (level == LOG_WARNING) {
    aliancedbLogger->setLevel(log4cxx::Level::getWarn());
  } else if (level == LOG_DEBUG) {
    aliancedbLogger->setLevel(log4cxx::Level::getDebug());
  } else if (level == LOG_INFO) {
    aliancedbLogger->setLevel(log4cxx::Level::getInfo());
  } else if (level == LOG_TRACE) {
    aliancedbLogger->setLevel(log4cxx::Level::getTrace());
  } else {
    ADB_ERROR("setLogLevel: log level not supported " << getDebugLevelAsString(level));
    throw Exception("Error while trying to change log level");
  }
#endif
}*/

#define ADB_NOT_IMPLEMENTED()                                                                                                    \
    do {                                                                                                                         \
        ADB_ERROR("Function Not Implemented!");                                                                                  \
        throw Exception("not implemented");                                                                                      \
    } while (0)

#endif //ADB_INCLUDE_UTILS_LOGGER_HPP_
