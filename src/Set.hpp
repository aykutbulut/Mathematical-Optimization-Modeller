#ifndef SET_HPP
#define SET_HPP

#include <string>

class Set {
  std::string const name_;
  int const size_;
public:
  Set(std::string const name, int size);
  int size() const;
};

#endif
