#ifndef INDEX_HPP
#define INDEX_HPP

#include <vector>
#include <string>

class Index {
  std::string name_;
  int const num_indices_;
  int * ind_;
public:
  Index(int num_indices, int const * ind);
  Index(std::vector<int> const ind);
  ~Index();
};

#endif
