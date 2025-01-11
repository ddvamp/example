#include <config.hpp>
#include <liba/src/liba.hpp>

#include <format>
#include <iostream>

int main(int argc, char **argv) {
  std::cout << argv[0] << " version " << EXAMPLE_VERSION_MAJOR << '.'
            << EXAMPLE_VERSION_MINOR << '.' << EXAMPLE_VERSION_PATCH
            << std::endl;

  std::cout << std::format("Hello, world#{}!", FooA()) << std::endl;

  return 0;
}
