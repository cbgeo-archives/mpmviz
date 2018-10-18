#ifndef MPM_VIZ_IO_H_
#define MPM_VIZ_IO_H_

#include <fstream>
#include <memory>
#include <string>

#include <boost/filesystem.hpp>

#include "tclap/CmdLine.h"
// Speed log
#include "spdlog/spdlog.h"

namespace mpmviz {
//! \brief Input/Output handler
class IO {
 public:
  //! Constructor with argc and argv
  //! \param[in] argc Number of input arguments
  //! \param[in] argv Input arguments
  IO(int argc, char** argv);

  //! Check if a file is present and valid
  //! \param[in] file_name Name of the file to check if it is present
  bool check_file(const std::string& file_name);

  //! Return the output folder for the analysis
  std::string output_folder() const;

  //! Create output file names (eg. velocity0000*.vtk)
  //! Generates a file based on attribute, current step and maxsteps
  //! \param[in] attribute Attribute being written (eg., velocity / stress)
  //! \param[in] file_extension File Extension (*.vtk or *.vtp)
  //! \param[in] step Current step
  //! \param[in] max_steps Total number of steps to be solved
  //! \return file_name File name with the correct attribute and a VTK extension
  boost::filesystem::path output_file(const std::string& attribute,
                                      const std::string& file_extension,
                                      const std::string& analysis_id,
                                      unsigned step, unsigned max_steps);

 private:
  //! Working directory
  std::string working_dir_;
  //! Logger
  std::shared_ptr<spdlog::logger> console_;
};

}  // namespace mpmviz
#endif  // MPM_VIZ_IO_H_
