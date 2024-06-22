#include "../controller/controller.h"

namespace s21 {

void Controller::parseFile(string path) {
  Parser::getInstance().parseFile(path);
}

vector<double> &Controller::getVertex() {
  return Parser::getInstance().getVertex();
}

vector<unsigned int> &Controller::getFacet() {
  return Parser::getInstance().getFacet();
}

void Controller::moveXYZ(double x, double y, double z) {
  Transform::getInstance().moveXYZ(x, y, z);
}

void Controller::rotateXYZ(char axis, double angle) {
  Transform::getInstance().rotateXYZ(axis, angle);  // !!!!!!!!
}

double &Controller::scale(double &zoom) {
  return Transform::getInstance().scale(zoom);
}

}  // namespace s21
