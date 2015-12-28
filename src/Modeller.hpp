#ifndef MODELLER_HPP
#define MODELLER_HPP

#include <vector>
#include <unordered_set>
#include <unordered_map>

class Variable;
class Set;

class Modeller {
  bool mapped_;
  std::unordered_set<Set*> sets_;
  std::unordered_set<Variable*> variables_;
  // index start for each variable
  std::unordered_map<Variable*,int> start_;
  void register_set(Set * set);
public:
  Modeller();
  ~Modeller();
  // check whether variable index sets are registered, if not register
  void register_variable(Variable * var);
  // given index is same order as var sets when var is constructed
  int get_index(Variable * var, std::vector<int> ind) const;
  int get_index(Variable * var, int size, int const * ind) const;
  // user has to call this before getting indices
  void build_map();
private:
  Modeller(Modeller const & other);
  Modeller & operator=(Modeller const rhs);
};

#endif
