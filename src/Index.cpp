#include <Index.hpp>

Index::Index(int num_indices,
	     int const * ind): num_indices_(num_indices), ind_(0) {
  ind_ = new int[num_indices_];
  std::copy(ind, ind+num_indices_, ind_);
}

Index::Index(std::vector<int> const ind): Index(ind.size(), &ind[0]) {
}

Index::~Index() {
  if (ind_) {
    delete[] ind_;
  }
}
