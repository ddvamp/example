cmake_minimum_required(VERSION 3.31)

project(
  example-examples
  LANGUAGES CXX
)

if (PROJECT_IS_TOP_LEVEL)
  message(FATAL_ERROR "$The example-examples project must not be top-level")
endif()

add_executable(example-examples)
target_sources(example-examples PRIVATE main.cpp)

set_target_properties(
  example-examples PROPERTIES

  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF

  DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
