#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::size_t;
using std::string;
using std::vector;

namespace s21 {

typedef struct {
  vector<double> vertex;
  vector<unsigned int> facet;
} data;

class Parser {
 private:
  data data_;

 public:
  static Parser &getInstance() {
    static Parser instance;
    return instance;
  }

  void parseFile(string path);
  vector<double> &getVertex();
  vector<unsigned int> &getFacet();
  void coord();

 private:
  Parser() : data_() {}
  ~Parser() {}
};

class Transform {
 public:
  static Transform &getInstance() {
    static Transform instance;
    return instance;
  }

  void moveXYZ(double x, double y, double z);
  void rotateXYZ(char axis, double angle);
  double &scale(double &zoom);

 private:
  Transform() {}
  ~Transform() {}
};

}  // namespace s21

#endif  // SINGLETON_H_
