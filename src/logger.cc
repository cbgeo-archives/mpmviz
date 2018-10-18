#include "logger.h"

// Create a logger for IO
const std::shared_ptr<spdlog::logger> mpm::Logger::io_logger =
    spdlog::stdout_color_st("IO");
