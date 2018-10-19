#include <memory>

#include "catch.hpp"

#include "io.h"
#include "particles.h"

// Check particles
TEST_CASE("Particles are checked for input parsing", "[particles][particle]") {

  // Initialise id and dimension
  const mpmviz::Index id = 0;
  const unsigned Dim = 3;
  // Create a particle object
  auto particles = std::make_unique<mpmviz::Particles>(id, Dim);
  // Check particles id
  REQUIRE(particles->id() == id);

  SECTION("Read a single HDF5 particles file") {
    // Assign argc and argv to nput arguments of MPM
    int argc = 3;
    // clang-format off
    char* argv[] = {(char*)"./mpmviz",
                    (char*)"-f",  (char*)"../hdf5-samples"};
    // clang-format on

    // Create an IO object
    auto io = std::make_unique<mpmviz::IO>(argc, argv);
    // HDF5 file
    const std::string filename = "../hdf5-samples/particles09.h5";

    // Number of particles before reading HDF5 file
    REQUIRE(particles->nparticles() == 0);
    // If particles file is found read
    if (io->check_file(filename)) particles->read_particles_hdf5(filename);

    // Number of particles after reading HDF5 file
    REQUIRE(particles->nparticles() == 8);
  }
}
