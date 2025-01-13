#include <config.hpp>

#include <liba/src/liba.hpp>

#include <format>
#include <iostream>

int main(int argc, char **argv) {
  std::cout << argv[0] << " version " << version::kMajor << '.'
            << version::kMinor << '.' << version::kPatch << '\n';

  std::cout << std::format("Hello, world #{}!", FooA()) << std::endl;

  return 0;
}
