#ifndef ROW_HPP
#define ROW_HPP

#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

class Variable;
class Modeller;

// Variable with indices
typedef std::pair<Variable*, std::vector<int> > VarIndex;

// struct VariableHash {
//   std::size_t operator()(Variable const *& v) const {
//     uintptr_t ad = (uintptr_t) v;
//     return (size_t) ((13*ad) ^ (ad >> 15));
//   }
// };

std::size_t VariableHash(Variable const * v) {
  uintptr_t ad = (uintptr_t) v;
  return (size_t) ((13*ad) ^ (ad >> 15));
}

struct VarIndexHash {
  std::size_t operator()(VarIndex const & x) const {
#if defined(__BOOST__)
    // use boost to hash x
#else
    std::size_t h1 = VariableHash(x.first);
    // hash vector value
    std::size_t h2 = 0;
    for(auto & i : x.second) {
      h2 ^= i + 0x9e3779b9 + (h2 << 6) + (h2 >> 2);
    }
    return h1 ^ (h2 << 1);
#endif
  }
};

struct VarIndexEqual {
  bool operator()(VarIndex const & lhs, VarIndex const & rhs) const {
    return (lhs.first==rhs.first) && (lhs.second==rhs.second);
  }
};

class Row {
  // terms_[pair(var,ind)] = coef
  std::unordered_map<VarIndex, double, VarIndexHash, VarIndexEqual> terms_;
  Modeller const * model_;
public:
  Row(Modeller const * model);
  Row(Modeller const * model, std::vector<Variable*> var,
      std::vector<std::vector<int> > var_ind,
      std::vector<double> coef);
  ~Row();
  void insert_term(Variable * var, std::vector<int> ind, double coef);
  void update_coef(Variable * var, std::vector<int> ind, double coef);
  // get number of varaibles in the row
  int size() const;
  // get variable indices
  void get_ind(int * ind) const;
  // get variable coefficients
  void get_coef(double * coef) const;
private:
  Row(Row const & other);
  Row & operator=(Row const rhs);
};

#endif
