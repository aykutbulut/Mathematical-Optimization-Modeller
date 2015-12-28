#include <Variable.hpp>

Variable::Variable(std::string const name,
		   std::vector<Set*> const ind_sets): name_(name),
						ind_sets_(ind_sets) {
}

std::vector<Set*> Variable::sets() {
  return ind_sets_;
}
