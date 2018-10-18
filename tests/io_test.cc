#include "catch.hpp"

#include "io.h"

// Check IO for input string
TEST_CASE("IO is checked for input parsing", "[IO]") {
  
    // Assign argc and argv to nput arguments of MPM
    int argc = 3;
    // clang-format off
    char* argv[] = {(char*)"./mpmviz",
                    (char*)"-f",  (char*)"./"};
    // clang-format on

    // Create an IO object
    auto io = std::make_unique<mpmviz::IO>(argc, argv);

    // Check if mpm.json exists
    REQUIRE(io->check_file("../README.md") == true);

    // Check if a non-existant file is present
    REQUIRE(io->check_file("fail.txt") == false);
    // Check input file name
    const std::string attribute = "geometry";
    const std::string extension = ".vtp";
    const std::string uuid_ = "MPM";
    unsigned step = 57;
    unsigned max_steps = 100;
    auto meshfile =
        io->output_file(attribute, extension, uuid_, step, max_steps).string();
    REQUIRE(meshfile == "./results/MPM/geometry057.vtp");
}
