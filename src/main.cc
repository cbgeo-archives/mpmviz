#include <memory>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include "spdlog/spdlog.h"

#include "io.h"
#include "logger.h"
#include "particles.h"

#include <iostream>

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

    const std::string filename = io->working_dir() + io->file();

    // If particles file is found read
    if (io->check_file(filename)) particles->read_particles_hdf5(filename);

    // Create a viz folder
    const std::string viz = io->working_dir() + "viz-houdini/";
    boost::filesystem::path dir(viz);
    if (!boost::filesystem::exists(dir))
      boost::filesystem::create_directory(dir);

    const std::string vizfile =
        viz + boost::filesystem::change_extension(io->file(), ".bgeo").string();
    particles->write_particles(vizfile);

  } catch (std::exception& exception) {
    console->error("MPM-Viz main: {}", exception.what());
  }
}
