#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include <vector>

class Set;

class Variable {
  std::string const name_;
  std::vector<Set*> ind_sets_;
public:
  Variable(std::string name, std::vector<Set*> ind_sets);
  std::vector<Set*> sets();
};

#endif
