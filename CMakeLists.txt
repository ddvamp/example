cmake_minimum_required(VERSION 3.21)

project(
  example
  VERSION 0.1.0
  DESCRIPTION "Project to study CMake"
  HOMEPAGE_URL "https://github.com/ddvamp/example"
  LANGUAGES CXX
)

if (NOT PROJECT_IS_TOP_LEVEL)
  message(FATAL_ERROR "Project must be top-level")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(name ${PROJECT_NAME})
set(dir ${PROJECT_SOURCE_DIR})

configure_file(${dir}/src/cmake/config.hpp.in ${dir}/src/config.hpp @ONLY)

add_executable(${name})

set_target_properties(
  ${name} PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION}

  # RUNTIME_OUTPUT_DIRECTORY "${dir}/build"
)

include(FetchContent)

FetchContent_Declare(
  liba
  GIT_REPOSITORY https://github.com/ddvamp/example-lib.git
  GIT_TAG e9a6ff1c75b6e6979c86fc5197796b894f549343
)

FetchContent_MakeAvailable(liba)

target_include_directories(${name} PUBLIC ${liba_SOURCE_DIR}/..)

target_link_libraries(${name} PRIVATE liba::liba)

file(GLOB_RECURSE sources ${dir}/src/*.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})
if (NOT sources)
  message(FATAL_ERROR "Sources not found in ${dir}/src")
endif()

target_include_directories(${name} PUBLIC ${dir})
target_sources(${name} PUBLIC ${sources})
