Mathematical-Optimization-Modeller [![Build Status](https://travis-ci.org/aykutbulut/Mathematical-Optimization-Modeller.svg?branch=master)](https://travis-ci.org/aykutbulut/Mathematical-Optimization-Modeller)
===
This is a library to help building mathematical optimization problems through C++ interface of any kind of solver. C++ interface of solvers work on sparse data which becomes messy very quickly when problems get more complicated. This library provides an interface closer to models written on papers and can get resulting structures in sparse forms which is preferred by most of the solvers.

Install
====
"./configure && make install" should work. It will create include and lib directories in the current directory and install headers and library to them.

If you want to install to a different location you can use "./configure --prefix=installation_path && amke install".
