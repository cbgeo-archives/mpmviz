#include "catch.hpp"

#include "io.h"

// Check IO for input string
TEST_CASE("IO is checked for input parsing", "[IO]") {

  // Assign argc and argv to nput arguments of MPM
  int argc = 3;
  // clang-format off
    char* argv[] = {(char*)"./mpmviz",
                    (char*)"-f",  (char*)"../hdf5-samples/"};
  // clang-format on

  // Create an IO object
  auto io = std::make_unique<mpmviz::IO>(argc, argv);

  // Check working dir
  REQUIRE(io->working_dir() == "../hdf5-samples/");

  // Check if mpm.json exists
  REQUIRE(io->check_file("../README.md") == true);

  // Check if a non-existant file is present
  REQUIRE(io->check_file("fail.txt") == false);
  // Check output file name
  const std::string attribute = "geometry";
  const std::string extension = ".vtp";
  unsigned step = 57;
  unsigned max_steps = 100;
  auto meshfile =
      io->output_file(attribute, extension, step, max_steps).string();
  REQUIRE(meshfile == "../hdf5-samples/viz/geometry057.vtp");
}
