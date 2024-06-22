#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../singleton/singleton.h"

namespace s21 {

class Controller {
 public:
  Controller() {}
  ~Controller() {}

 public:
  static Controller &getInstance() {
    static Controller instance;
    return instance;
  }

  void parseFile(string path);

  void moveXYZ(double x, double y, double z);
  void rotateXYZ(char axis, double angle);
  double &scale(double &zoom);

  vector<double> &getVertex();
  vector<unsigned int> &getFacet();
};

}  // namespace s21

#endif  // CONTROLLER_H_
