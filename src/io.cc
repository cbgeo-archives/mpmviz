#include "io.h"

//! Constructor with argc and argv
mpmviz::IO::IO(int argc, char** argv) {
  //! Logger
  console_ = spdlog::get("IO");
  try {
    // Set title
    TCLAP::CmdLine cmd("MPM-VIZ (CB-Geo)", ' ', "Alpha V1.0");

    // Define working directory
    TCLAP::ValueArg<std::string> cwd_arg(
        "f", "working_dir", "Current working folder", true, "", "working_dir");
    cmd.add(cwd_arg);

    // Parse arguments
    cmd.parse(argc, argv);

    // Set working directory
    working_dir_ = cwd_arg.getValue();

  } catch (TCLAP::ArgException& except) {  // catch any exceptions
    console_->error("error: {}  for arg {}", except.error(), except.argId());
  }
}

//! Check if a file is present
bool mpmviz::IO::check_file(const std::string& filename) {
  bool status = false;

  // Check if file is present
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(filename);
    status = true;
    file.close();
  } catch (std::ifstream::failure& exception) {
    status = false;
    console_->error("Failed to find file {}: {}", filename, exception.what());
  }
  return status;
}

//! Create output VTK file names (eg. Velocity0000*.vtk)
boost::filesystem::path mpmviz::IO::output_file(
    const std::string& attribute, const std::string& file_extension,
    const std::string& analysis_id, unsigned step, unsigned max_steps) {
  std::stringstream file_name;
  std::string path = "results/";

  std::string attribute_name = attribute;

#ifdef USE_MPI
  int mpi_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  // Get number of MPI ranks
  int mpi_size;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

  if (mpi_size > 1)
    attribute_name +=
        "-" + std::to_string(mpi_rank) + "_" + std::to_string(mpi_size) + "-";
#endif

  file_name.str(std::string());
  file_name << attribute_name;
  file_name.fill('0');
  int digits = log10(max_steps) + 1;
  file_name.width(digits);
  file_name << step;
  file_name << file_extension;

  // Include path
  if (!path.empty()) path = working_dir_ + path;

  // Create results folder if not present
  boost::filesystem::path dir(path);
  if (!boost::filesystem::exists(dir)) boost::filesystem::create_directory(dir);

  // Create analysis folder
  path += analysis_id + "/";
  dir = path;
  if (!boost::filesystem::exists(dir)) boost::filesystem::create_directory(dir);

  boost::filesystem::path file_path(path + file_name.str().c_str());
  return file_path;
}
