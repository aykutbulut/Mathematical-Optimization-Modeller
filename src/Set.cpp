#include <Set.hpp>

Set::Set(std::string const name, int size): name_(name), size_(size) {
}

int Set::size() const {
  return size_;
}
