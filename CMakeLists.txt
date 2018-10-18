project(mpmviz LANGUAGES CXX)

# Require C++14-compliant compiler; only available for CMake v. 3.1 and up
set(CMAKE_CXX_STANDARD 14)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
 SET(CMAKE_BUILD_TYPE "Debug")
 #SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

# Intel specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

# Clang specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-var-template")
endif()

# CMake seems to have no way to enable/disable testing per subproject,
# so we provide an option similar to BUILD_TESTING, but just for MPMVIZ.
option(MPMVIZ_BUILD_TESTING "enable testing for mpmviz" ON)

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Boost Archive
find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${BOOST_INCLUDE_DIRS})
link_libraries(${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# HDF5
ENABLE_LANGUAGE(C)
find_package(HDF5 COMPONENTS CXX HL)
if (HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIRS})
  link_libraries(${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES} ${HDF5_CXX_HL_LIBRARIES})
  add_definitions(${HDF5_DEFINITIONS})
endif()

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif()

# pthreads
find_package (Threads)
link_libraries (${CMAKE_THREAD_LIBS_INIT})

# VTK
find_package(VTK)
if (VTK_FOUND)
  include(${VTK_USE_FILE})
  link_libraries(${VTK_LIBRARIES})
  add_definitions("-DUSE_VTK")
  set(mpmviz_vtk ${mpmviz_SOURCE_DIR}/src/vtk_writer.cc)
endif()

# Include directories
include_directories(BEFORE
  ${mpmviz_SOURCE_DIR}/include/
  ${mpmviz_SOURCE_DIR}/external/
)

# mpmviz executable
SET(mpmviz_src
  ${mpmviz_SOURCE_DIR}/src/io.cc
  ${mpmviz_SOURCE_DIR}/src/logger.cc
)

add_library(lmpmviz SHARED ${mpmviz_src} ${mpmviz_vtk})

add_executable(mpmviz ${mpmviz_SOURCE_DIR}/src/main.cc)
target_link_libraries(mpmviz lmpmviz)

# Unit test
if(MPMVIZ_BUILD_TESTING)
  SET(test_src
    ${mpmviz_SOURCE_DIR}/tests/test_main.cc
    ${mpmviz_SOURCE_DIR}/tests/io_test.cc
  )
  add_executable(mpmviz-test ${test_src})
  target_link_libraries(mpmviz-test lmpmviz)
  add_test(NAME mpmviz-test COMMAND $<TARGET_FILE:mpmviz-test>)
  enable_testing()
endif()

# Coverage
find_package(codecov)
if(ENABLE_COVERAGE)
  add_executable(mpmviz-test_coverage ${mpmviz_vtk} ${mpmviz_src} ${test_src})
  add_coverage(mpmviz-test_coverage)
endif()
