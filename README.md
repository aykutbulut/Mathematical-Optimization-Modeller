Mathematical-Optimization-Modeller [![Build Status](https://travis-ci.org/aykutbulut/Mathematical-Optimization-Modeller.svg?branch=master)](https://travis-ci.org/aykutbulut/Mathematical-Optimization-Modeller)
===
This is a library to help building mathematical optimization problems through C++ interface of any kind of solver. C++ interface of solvers work on sparse data which becomes messy very quickly when problems get more complicated. This library provides an interface closer to models written on papers and can get resulting structures in sparse forms which is preferred by most of the solvers.

Install
====
"./configure && make install" should work. It will create include and lib directories in the current directory and install headers and library to them.

If you want to install to a different location you can use "./configure --prefix=installation_path && make install".

Basic Idea in a nutshell
====
Most of C/C++ interfaces (Cplex, Mosek, COIN-OR OSI) uses sparse data structures to build optimization models. Keeping track of problem variable and row indices is messy using a C/C++ solver interface. This library keeps track of indices for you. You can create rows and then querry the sparse form to add your choice of solver itnerface. This library makes it easier to load optimization models on paper to C/C++ interfaces.

Create a modeller object
```C++
  Modeller * model = new Modeller();
```
  
 
Create index sets.
```C++
  Set * I = new Set("I", 2);
  Set * J = new Set("J", 3);
```

Creating a variable with index set I and J.
```C++
  Variable * x = new Variable("x", std::vector<Set*>({I, J}));
```

Register varible to the model
```C++
  model->register_variable(x);
```
  
After registering all your variables call build_map() function, which maps all variables (x_ij s) to an index.
```C++
  model->build_map();
```

From now on when you need to get the index for variable x_ij, you can use
  model->get_index(x, std::vector<int>({i,j}))
  
You can also create rows using variables you defined. The following code block creates a set of constraints.
```C++
  // this c++ code snippet generates following constraint set (vectors on the left hand side only)
  // sum (i in I) x_ij = 1 (for all j in J)
  std::vector<Row*> rows;
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
```

Then you can get sparse form of the rows generated using 
```C++
  for (auto const & r: rows) {
    int size = r->size();
    int * indices = new int[size];
    double * coefficients = new double[size];
    r->get_ind(indices);
    r->get_coef(coefficient);
    // do whatever you want with sparse row, nonzero column indices are stored at "indices"
    // the corresponding coefficients are stored in "coefficients".
    delete[] indices;
    delete[] coefficients;
  }
```

See examples directory for complete examples.
