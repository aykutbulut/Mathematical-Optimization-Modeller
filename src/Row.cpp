#include <Row.hpp>
#include <Modeller.hpp>
#include <iostream>

Row::Row(Modeller const * model): model_(model) {
  terms_.clear();
}

Row::Row(Modeller const * model, std::vector<Variable*> var,
	 std::vector<std::vector<int> > var_ind,
	 std::vector<double> coef): model_(model) {
  terms_.clear();
  int size = var.size();
  for (int i=0; i<size; ++i) {
    terms_[VarIndex(var[i], var_ind[i])] = coef[i];
  }
}

Row::~Row() {
  terms_.clear();
  model_ = 0;
}

void Row::insert_term(Variable * var, std::vector<int> ind, double coef) {
  if (terms_.find(VarIndex(var,ind))==terms_.end()) {
    terms_[VarIndex(var,ind)] = coef;
  }
  else {
    std::cerr << "Variable is already in the row, try update_coef()!" << std::endl;
    throw std::exception();
  }
}

void Row::update_coef(Variable * var, std::vector<int> ind, double coef) {
  if (terms_.find(VarIndex(var,ind))==terms_.end()) {
    std::cerr << "Variable is not in the row, try insert_term()!" << std::endl;
    throw std::exception();
  }
  else {
    terms_[VarIndex(var,ind)] = coef;
  }
}

int Row::size() const {
  return terms_.size();
}

void Row::get_ind(int * ind) const {
  int i=0;
  for (auto const & t: terms_) {
    ind[i++] = model_->get_index(t.first.first, t.first.second);
  }
}

void Row::get_coef(double * coef) const {
  int i=0;
  for (auto & t: terms_) {
    coef[i++] = terms_.at(t.first);
  }
}


// const std::pair<const std::pair<Variable*, std::vector<int> >, double>&

// candidates:
// const std::pair<const std::pair<Variable*, std::vector<int> >, double> to
// const key_type& {aka const std::pair<Variable*, std::vector<int> >&}
