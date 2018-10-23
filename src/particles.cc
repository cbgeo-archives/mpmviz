#include "particles.h"

// Constructor with id and dimension
mpmviz::Particles::Particles(Index id, unsigned dim) : id_{id}, dim_{dim} {
  //! Logger
  const std::string logger =
      "Particles" + std::to_string(dim) + "d::" + std::to_string(id);
  console_ = std::make_unique<spdlog::logger>(logger, mpm::stdout_sink);
  particles_.clear();
}

// Read Particles from HDF5 file
bool mpmviz::Particles::read_particles_hdf5(const std::string& filename) {

  // Create a new file using default properties.
  hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  // Throw an error if file can't be found
  if (file_id < 0) throw std::runtime_error("HDF5 particle file is not found");

  // Get table details
  hsize_t nfields;
  hsize_t nrecords;
  herr_t err = H5TBget_table_info(file_id, "table", &nfields, &nrecords);

  console_->info("Reading HDF5 table file: {}, info: nfields: {} nrecords: {}",
                 filename, nfields, nrecords);

  // Calculate the size and the offsets of our struct members in memory
  const hsize_t NRECORDS = nrecords;

  const hsize_t NFIELDS = 24;

  size_t dst_size = sizeof(HDF5Particle);
  size_t dst_offset[NFIELDS] = {
      HOFFSET(HDF5Particle, id),         HOFFSET(HDF5Particle, mass),
      HOFFSET(HDF5Particle, volume),     HOFFSET(HDF5Particle, pressure),
      HOFFSET(HDF5Particle, coord_x),    HOFFSET(HDF5Particle, coord_y),
      HOFFSET(HDF5Particle, coord_z),    HOFFSET(HDF5Particle, velocity_x),
      HOFFSET(HDF5Particle, velocity_y), HOFFSET(HDF5Particle, velocity_z),
      HOFFSET(HDF5Particle, stress_xx),  HOFFSET(HDF5Particle, stress_yy),
      HOFFSET(HDF5Particle, stress_zz),  HOFFSET(HDF5Particle, tau_xy),
      HOFFSET(HDF5Particle, tau_yz),     HOFFSET(HDF5Particle, tau_xz),
      HOFFSET(HDF5Particle, strain_xx),  HOFFSET(HDF5Particle, strain_yy),
      HOFFSET(HDF5Particle, strain_zz),  HOFFSET(HDF5Particle, gamma_xy),
      HOFFSET(HDF5Particle, gamma_yz),   HOFFSET(HDF5Particle, gamma_xz),
      HOFFSET(HDF5Particle, epsilon_v),  HOFFSET(HDF5Particle, status),
  };

  // To get size
  HDF5Particle particle;

  size_t dst_sizes[NFIELDS] = {
      sizeof(particle.id),         sizeof(particle.mass),
      sizeof(particle.volume),     sizeof(particle.pressure),
      sizeof(particle.coord_x),    sizeof(particle.coord_y),
      sizeof(particle.coord_z),    sizeof(particle.velocity_x),
      sizeof(particle.velocity_y), sizeof(particle.velocity_z),
      sizeof(particle.stress_xx),  sizeof(particle.stress_yy),
      sizeof(particle.stress_zz),  sizeof(particle.tau_xy),
      sizeof(particle.tau_yz),     sizeof(particle.tau_xz),
      sizeof(particle.strain_xx),  sizeof(particle.strain_yy),
      sizeof(particle.strain_zz),  sizeof(particle.gamma_xy),
      sizeof(particle.gamma_yz),   sizeof(particle.gamma_xz),
      sizeof(particle.epsilon_v),  sizeof(particle.status),
  };

  std::vector<HDF5Particle> dst_buf;
  dst_buf.reserve(NRECORDS);
  // Read the table
  H5TBread_table(file_id, "table", dst_size, dst_offset, dst_sizes,
                 dst_buf.data());

  for (unsigned i = 0; i < NRECORDS; ++i) {
    particle = dst_buf[i];
    particles_.emplace_back(particle);
  }
  // close the file
  H5Fclose(file_id);
  return true;
}

// Write particles
bool mpmviz::Particles::write_particles(const std::string& filename) {
  bool status = true;
  try {
    if (particles_.empty())
      throw std::runtime_error("No particles have been initialised!");

    Partio::ParticlesDataMutable* parts = Partio::create();
    Partio::ParticleAttribute postition, velocity, mass, index;

    index = parts->addAttribute("index", Partio::INT, 1);
    mass = parts->addAttribute("m", Partio::VECTOR, 1);
    postition = parts->addAttribute("position", Partio::VECTOR, 3);
    velocity = parts->addAttribute("v", Partio::VECTOR, 3);

    for (const auto& particle : particles_) {
      // Add particle and get index
      int idx = parts->addParticle();
      // Index
      int* index_p = parts->dataWrite<int>(index, idx);
      index_p[0] = particle.id;

      // Write mass
      float* mass_p = parts->dataWrite<float>(mass, idx);
      mass_p[0] = particle.mass;

      // Write velocity and position
      float* velocity_p = parts->dataWrite<float>(velocity, idx);
      velocity_p[0] = particle.velocity_x;
      velocity_p[1] = particle.velocity_y;
      velocity_p[2] = particle.velocity_z;

      float* position_p = parts->dataWrite<float>(postition, idx);
      position_p[0] = particle.coord_x;
      position_p[1] = particle.coord_y;
      position_p[2] = particle.coord_z;
    }
    Partio::write(filename.c_str(), *parts);
    parts->release();

  } catch (std::exception& exception) {
    console_->error("{} #{}: {}\n", __FILE__, __LINE__, exception.what());
    status = false;
  }
  return status;
}
