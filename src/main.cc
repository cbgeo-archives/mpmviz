#include <memory>

#include "spdlog/spdlog.h"

#include "io.h"
#include "logger.h"

int main(int argc, char** argv) {
  // Logger level (trace, debug, info, warn, error, critical, off)
  spdlog::set_level(spdlog::level::trace);

  // Initialise logger
  auto console = spdlog::stdout_color_mt("main");

  try {
    // Create an IO object
    auto io = std::make_unique<mpmviz::IO>(argc, argv);

  } catch (std::exception& exception) {
    console->error("MPM-Viz main: {}", exception.what());
  }
}
