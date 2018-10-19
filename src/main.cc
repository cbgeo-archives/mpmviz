#include <memory>

#include "spdlog/spdlog.h"

#include "io.h"
#include "logger.h"
#include "particles.h"

int main(int argc, char** argv) {
  // Logger level (trace, debug, info, warn, error, critical, off)
  spdlog::set_level(spdlog::level::trace);

  // Initialise logger
  auto console = spdlog::stdout_color_mt("main");

  try {
    // Create an IO object
    auto io = std::make_unique<mpmviz::IO>(argc, argv);
    // Initialise id and dimension
    const mpmviz::Index id = 0;
    const unsigned Dim = 3;
    // Create a particle object
    auto particles = std::make_unique<mpmviz::Particles>(id, Dim);

    const std::string filename = io->working_dir() + "particles09.h5";

    // If particles file is found read
    if (io->check_file(filename)) particles->read_particles_hdf5(filename);

  } catch (std::exception& exception) {
    console->error("MPM-Viz main: {}", exception.what());
  }
}
