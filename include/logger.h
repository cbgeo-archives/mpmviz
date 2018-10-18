#ifndef MPM_LOGGER_H_
#define MPM_LOGGER_H_

#include <memory>

// Speed log
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

//! MPM namespace
namespace mpm {

// Create an stdout colour sink
const std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> stdout_sink =
    std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

struct Logger {
  // Create a logger for IO
  static const std::shared_ptr<spdlog::logger> io_logger;
};

}  // namespace mpm

#endif  // MPM_LOGGER_H_
