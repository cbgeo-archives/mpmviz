#ifndef MPMVIZ_PARTICLES_H_
#define MPMVIZ_PARTICLES_H_

#include <memory>
#include <vector>

#include <Partio.h>

#include "hdf5_particle.h"
#include "logger.h"

namespace mpmviz {

//! Global index type for the particles
using Index = unsigned long long;

//! Particles class
//! \brief Particles class to store all properties
class Particles {
 public:
  //! Constructor with id and dimension
  //! \param[in] id Particles set id
  //! \param[in] dim Dimension of all particles
  Particles(Index id, unsigned dim);

  //! Return id
  Index id() const { return id_; }

  //! Read HDF5 particles file
  //! \param[in] filename Input HDF5 particle file
  bool read_particles_hdf5(const std::string& filename);

  //! Return number of particles
  size_t nparticles() const { return particles_.size(); }

  //! Write particles
  //! \param[in] filename Output particles filename
  bool write_particles(const std::string& filename);

 private:
  // ID of particles
  Index id_;
  // Dimension
  unsigned dim_;
  // Vector of particles
  std::vector<HDF5Particle> particles_;
  //! Logger
  std::unique_ptr<spdlog::logger> console_;
};

}  // namespace mpmviz

#endif  // MPMVIZ_PARTICLES_H_
