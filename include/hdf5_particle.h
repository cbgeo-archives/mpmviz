#ifndef MPMVIZ_HDF5_PARTICLE_H_
#define MPMVIZ_HDF5_PARTICLE_H_

// HDF5
#include "hdf5.h"
#include "hdf5_hl.h"

namespace mpmviz {

//! Global index type for the particles
using Index = unsigned long long;

// Define a struct of particle
typedef struct HDF5Particle {
  // Index
  mpmviz::Index id;
  // Mass
  double mass;
  // Volume
  double volume;
  // Pressure
  double pressure;
  // Coordinates
  double coord_x, coord_y, coord_z;
  // Velocity
  double velocity_x, velocity_y, velocity_z;
  // Stresses
  double stress_xx, stress_yy, stress_zz;
  double tau_xy, tau_yz, tau_xz;
  // Strains
  double strain_xx, strain_yy, strain_zz;
  double gamma_xy, gamma_yz, gamma_xz;
  // Volumetric strain centroid
  double epsilon_v;
  // Status
  bool status;
} HDF5Particle;

}  // namespace mpmviz

#endif  // MPMVIZ_HDF5_PARTICLE_H_
