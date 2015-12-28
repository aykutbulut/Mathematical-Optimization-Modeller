#include <iostream>

#include <Modeller.hpp>
#include <Set.hpp>
#include <Variable.hpp>
#include <Index.hpp>

Modeller::Modeller(): mapped_(false) {
  sets_.clear();
  variables_.clear();
}

Modeller::~Modeller() {
  sets_.clear();
  variables_.clear();
  start_.clear();
}

// create maps for each variable, mapping works as follows,
// map in the order of iteration of variables ie., variables_.begin()
// to variables_.end();
// for indices mapping works as follows,
// assume x is the first variable, then index for x(i,j,k) is
// i*|J|*|K| + j*|K| + k
//
void Modeller::build_map() {
  start_.clear();
  mapped_ = true;
  // compute starts
  int start = 0;
  for (auto const & v: variables_) {
    start_[v] = start;
    int prod = 1;
    for (auto const s: v->sets()) {
      prod *= s->size();
    }
    start += prod;
  }
  // now we know starts and index  is mapped as follows,
  // index for x(i,j,k) is start_[x]+i*|J|*|K| + j*|K| + k
}

void Modeller::register_variable(Variable * var) {
  if (mapped_) {
    mapped_ = false;
  }
  if (variables_.find(var)==variables_.end()) {
    // register all index sets of var
    for (auto const & s: var->sets()) {
      if (sets_.find(s)==sets_.end()) {
	register_set(s);
      }
    }
    // insert var
    variables_.insert(var);
  }
  else {
    std::cerr << "Variable is already registered!" << std::endl;
    throw std::exception();
  }
}

// todo(aykut): can you make variable input const?
int Modeller::get_index(Variable * var,
			std::vector<int> ind) const {
  if (mapped_==false) {
    std::cerr << "build_map() should be called before getting incides!"
	      << std::endl;
    throw std::exception();
  }
  return get_index(var, ind.size(), &ind[0]);
}

// return index of a given variable with given indices
int Modeller::get_index(Variable * var, int size,
			int const * ind) const {
  if (mapped_==false) {
    std::cerr << "build_map() should be called before getting incides!"
	      << std::endl;
    throw std::exception();
  }
  // find variable
  if (variables_.find(var)==variables_.end()) {
    std::cerr << "Variable is not registered!" << std::endl;
    throw std::exception();
  }
  if (start_.find(var)==start_.end()) {
    std::cerr << "Variable is not mapped. This should not happen!" << std::endl;
    throw std::exception();
  }
  // now we know starts and index  is mapped as follows,
  // index for x(i,j,k) is start_[x]+i*|J|*|K| + j*|K| + k
  int index = start_.at(var);
  int mul_factor = 1;
  for (int i=size-1; i>=0; --i) {
    index += ind[i]*mul_factor;
    mul_factor = mul_factor * var->sets()[i]->size();
  }
  return index;
}

void Modeller::register_set(Set * set) {
  if (mapped_) {
    mapped_ = false;
  }
  if (sets_.find(set)==sets_.end()) {
    sets_.insert(set);
  }
  else {
    std::cerr << "Set is already registered!" << std::endl;
    throw std::exception();
  }
}
