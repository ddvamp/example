cmake_minimum_required(VERSION 3.31)

project(
  example-tests
  LANGUAGES CXX
)

set(name ${PROJECT_NAME})

if (PROJECT_IS_TOP_LEVEL)
  message(FATAL_ERROR "The ${name} project must not be top-level")
endif()

add_executable(${name})
target_sources(${name} PRIVATE main.cpp)

set_target_properties(
  ${name} PROPERTIES

  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF

  DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
