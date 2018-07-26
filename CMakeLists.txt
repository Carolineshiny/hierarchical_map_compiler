cmake_minimum_required(VERSION 3.2)
project(hierarchical_map_compiler)
include_directories(include)
#link_directories(lib)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
include(ExternalProject)
ExternalProject_Add(sdd_github
  GIT_REPOSITORY   https://github.com/hahaXD/sdd.git
  GIT_TAG          master
  STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  )
add_library(sdd UNKNOWN IMPORTED)
ExternalProject_Get_Property(sdd_github binary_dir)
set_target_properties(sdd PROPERTIES IMPORTED_LOCATION ${binary_dir}/libsdd.a)
add_dependencies(sdd sdd_github-build)

ExternalProject_Add(psdd_github
  GIT_REPOSITORY   https://github.com/hahaXD/psdd.git
  GIT_TAG          master
  STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  )
add_library(psdd UNKNOWN IMPORTED)
ExternalProject_Get_Property(psdd_github binary_dir)
set_target_properties(psdd PROPERTIES IMPORTED_LOCATION ${binary_dir}/libpsdd.a)
add_dependencies(psdd psdd_github-build)


ExternalProject_Add(googletest_github
  GIT_REPOSITORY   https://github.com/google/googletest.git
  GIT_TAG          master
  STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  )

ExternalProject_Get_Property(googletest_github binary_dir)
add_library(gtest UNKNOWN IMPORTED)
add_library(gtest_main UNKNOWN IMPORTED)
set_target_properties(gtest PROPERTIES
  IMPORTED_LOCATION ${binary_dir}/googlemock/gtest/libgtest.a
  )
set_target_properties(gtest_main PROPERTIES
  IMPORTED_LOCATION ${binary_dir}/googlemock/gtest/libgtest_main.a
  )
add_dependencies(gtest googletest_github-build)
add_dependencies(gtest_main googletest_github-build)


ExternalProject_Add(htd_github
  GIT_REPOSITORY   https://github.com/mabseher/htd.git
  GIT_TAG          master
  STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  )
add_library(htd UNKNOWN IMPORTED)
ExternalProject_Get_Property(htd_github binary_dir)
if(UNIX AND NOT APPLE)
  set_target_properties(htd PROPERTIES IMPORTED_LOCATION ${binary_dir}/lib/libhtd.so)
endif(UNIX AND NOT APPLE)

if(APPLE)
  set_target_properties(htd PROPERTIES IMPORTED_LOCATION ${binary_dir}/lib/libhtd.0.dylib)
endif(APPLE)
add_dependencies(htd htd_github-build)




include_directories(include)
file(GLOB HIERARCHICAL_MAP_COMPILER_SRC_FILES "src/*.h" "src/*.cpp" "src/*.c")
file(GLOB HIERARCHICAL_MAP_COMPILER_TEST_SRC_FILES "test/*.cpp")
add_library(hmc ${HIERARCHICAL_MAP_COMPILER_SRC_FILES})
add_executable(hmc_test ${HIERARCHICAL_MAP_COMPILER_TEST_SRC_FILES})
add_executable(hmc_main main.cpp)
target_link_libraries(hmc psdd sdd gmp htd)
target_link_libraries(hmc_test hmc psdd sdd gmp gtest gtest_main htd pthread)
target_link_libraries(hmc_main hmc psdd sdd gmp htd)
