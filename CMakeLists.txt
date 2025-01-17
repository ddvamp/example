cmake_minimum_required(VERSION 3.31)

project(
  example
  VERSION 0.1.0
  DESCRIPTION "Project to study CMake"
  HOMEPAGE_URL "https://github.com/ddvamp/example"
  LANGUAGES CXX
)

set(name ${PROJECT_NAME})
set(dir ${PROJECT_SOURCE_DIR})

if (NOT PROJECT_IS_TOP_LEVEL)
  message(FATAL_ERROR "$The {name} project must be top-level")
endif()

if (NOT EXISTS ${dir}/src/main.cpp)
  message(FATAL_ERROR "No main.cpp file found in ${dir}/src")
endif()

include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(bindir ${dir}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bindir}/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bindir}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bindir}/other)
unset(bindir)

set(CMAKE_DEBUG_POSTFIX d)

configure_file(${dir}/src/config.hpp.in ${dir}/src/cmake/config.hpp @ONLY)

add_compile_definitions(${MY_COMPILE_DEFINITIONS})
add_compile_options(${MY_COMPILE_OPTIONS})
add_link_options(${MY_LINK_OPTIONS})

# ------------------------------------------------------------------------------
# project target
# ------------------------------------------------------------------------------

add_executable(${name})

set_target_properties(
  ${name} PROPERTIES

  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF

  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}

  DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

target_include_directories(${name} PRIVATE ${dir}/src ${dir}/src/cmake)
file(GLOB_RECURSE sources ${dir}/src/*.cpp)
target_sources(${name} PRIVATE ${sources})

# ------------------------------------------------------------------------------
# libraries
# ------------------------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
  liba
  GIT_REPOSITORY https://github.com/ddvamp/example-lib.git
  GIT_TAG origin/main
  GIT_SHALLOW ON
  GIT_PROGRESS ON
  SOURCE_DIR ${dir}/lib/liba
  BINARY_DIR lib/liba
)

FetchContent_MakeAvailable(liba)

target_link_libraries(${name} PRIVATE liba)

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------

install(TARGETS ${name} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# ------------------------------------------------------------------------------
# tests and examples
# ------------------------------------------------------------------------------

string(TOUPPER ${name}_BUILD_TESTS tests)
option(${tests} "Build tests for ${name}" OFF)
if(${tests})
  enable_testing()
  add_subdirectory(test)
endif()

string(TOUPPER ${name}_BUILD_EXAMPLES examples)
option(${examples} "Build examples for ${name}" OFF)
if(${examples})
  add_subdirectory(example)
endif()
