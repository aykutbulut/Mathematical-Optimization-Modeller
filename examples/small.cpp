#include <iostream>

#include <Variable.hpp>
#include <Set.hpp>
#include <Modeller.hpp>
#include <Row.hpp>

// assume we have the following LP
//
// min sum (i in I, j in J) x_ij
// s.t.
// sum (i in I) x_ij = 1              (for all j in J)
// sum (j in J, j<i) x_ij - y_i >= 1  (for all i in I)
// x_ij >= 0                          (for all i in I, j in J)
// y_i  >= 0                          (for all i in I)
//

int main() {
  Modeller * model = new Modeller();
  // create sets
  Set * I = new Set("I", 2);
  Set * J = new Set("J", 3);
  Variable * x = new Variable("x", std::vector<Set*>({I, J}));
  Variable * y = new Variable("y", std::vector<Set*>({I}));
  model->register_variable(x);
  model->register_variable(y);
  // call build_model after registering all variables.
  model->build_map();
  // print variable indices
  for (int i=0; i<I->size(); ++i) {
    for (int j=0; j<J->size(); ++j) {
      std::cout << "x_" << i << j << " "
		<< model->get_index(x, std::vector<int>({i,j}))
		<< std::endl;
    }
  }
  for (int i=0; i<I->size(); ++i) {
      std::cout << "y_" << i << "  "
		<< model->get_index(y, std::vector<int>({i}))
		<< std::endl;
  }
  // create rows
  std::vector<Row*> rows;
  // first group of rows
  for (int j=0; j<J->size(); ++j) {
    std::vector<Variable*> vars(I->size(), x);
    std::vector<std::vector<int> > ind;
    std::vector<double> coef(I->size(), 1.0);
    for (int i=0; i<I->size(); ++i) {
      ind.push_back(std::vector<int>({i,j}));
    }
    rows.push_back(new Row(model, vars, ind, coef));
    vars.clear();
    coef.clear();ind.clear();
  }
  // second group of rows
  for (int i=0; i<I->size(); ++i) {
    std::vector<Variable*> vars(i, x);
    vars.push_back(y);
    std::vector<double> coef(i, 1.0);
    coef.push_back(-1.0);
    std::vector<std::vector<int> > ind;
    for (int j=0; j<i; ++j) {
      ind.push_back(std::vector<int>({i,j}));
    }
    ind.push_back(std::vector<int>({i}));
    rows.push_back(new Row(model, vars, ind, coef));
    vars.clear();
    coef.clear();
    ind.clear();
  }
  // print rows
  for (auto const & r: rows) {
    std::cout << "row start" << std::endl;
    // print indices
    int size = r->size();
    int * ind = new int[size];
    r->get_ind(ind);
    std::cout << "ind: ";
    for (int i=0; i<size; ++i) {
      std::cout << ind[i] << " ";
    }
    std::cout << std::endl;
    // print elements
    double * coef = new double[size];
    r->get_coef(coef);
    std::cout << "val: ";
    for (int i=0; i<size; ++i) {
      std::cout << coef[i] << " ";
    }
    std::cout << std::endl;
    delete[] ind;
    delete[] coef;
  }
  delete I;
  delete J;
  delete x;
  delete y;
  delete model;
  for (auto & r: rows) {
    delete r;
  }
  rows.clear();
  return 0;
}
