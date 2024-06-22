#include "singleton.h"
namespace s21 {

void Parser::parseFile(string path) {
  string str;
  std::ifstream file(path);
  data_.vertex.clear();
  data_.facet.clear();

  if (!file.is_open()) return;

  while (std::getline(file, str)) {
    if (str[0] == 'v' && str[1] == ' ') {
      size_t pos = 0;
      size_t count = 0;
      for (size_t i = 0; i < 3; ++i) {
        pos = str.find_first_of("-0123456789", pos);
        data_.vertex.push_back(std::stod(&str[pos], &count));
        pos += count;
      }
    }

    if (str[0] == 'f' && str[1] == ' ') {
      size_t count = 0;

      vector<unsigned int> x;
      for (size_t i = 1; i < str.length(); ++i) {
        if (str[i] == ' ' && str[i + 1] >= '0' && str[i + 1] <= '9') {
          data_.facet.push_back(std::stod(&str[i]) - 1);
          ++count;
          if (count == 3) break;
        };
      }
    }
  }

  file.close();
  vector<unsigned int> facet;
  for (size_t i = 0; i < data_.facet.size(); ++i) {
    if (i % 3 == 2) {
      facet.push_back(data_.facet[i]);
      facet.push_back(data_.facet[i - 2]);
    } else {
      facet.push_back(data_.facet[i]);
      facet.push_back(data_.facet[i + 1]);
    }
  }
  coord();
  data_.facet = facet;
}

void Parser::coord() {
  if (getVertex().size()) {
    std::pair minmax =
        std::minmax_element(getVertex().begin(), getVertex().end());
    double max =
        400.0 / std::max(std::abs(*minmax.first), std::abs(*minmax.second));
    for (double &item : getVertex()) {
      item *= max;
    }
  }
}

std::vector<double> &Parser::getVertex() { return data_.vertex; }

std::vector<unsigned int> &Parser::getFacet() { return data_.facet; }

void Transform::moveXYZ(double x, double y, double z) {
  std::vector<double> &vertex = Parser::getInstance().getVertex();

  for (size_t i = 0; i < vertex.size(); i += 3) {
    vertex[i] += x;
    vertex[i + 1] += y;
    vertex[i + 2] += z;
  }
}

double &Transform::scale(double &zoom) {
  static double zoom_prev = 1.0;

  if (zoom == 1.0) zoom = 1.0 / zoom_prev;

  for (double &item : Parser::getInstance().getVertex()) {
    item *= zoom;
  }
  zoom_prev *= zoom;
  return zoom_prev;
}

void Transform::rotateXYZ(char axis, double angle) {
  int a = 0;
  int b = 0;
  double prev_angle = 0.0;
  static double prev_angle_x = 0.0;
  static double prev_angle_y = 0.0;
  static double prev_angle_z = 0.0;
  switch (axis) {
    case 'x':
      prev_angle = prev_angle_x;
      a = 1;
      b = 2;
      break;
    case 'y':
      prev_angle = prev_angle_y;
      a = 0;
      b = 2;
      break;
    case 'z':
      prev_angle = prev_angle_z;
      a = 0;
      b = 1;
      break;
  }

  for (size_t x = 0; x < Parser::getInstance().getVertex().size(); x += 3) {
    double temp_1 = Parser::getInstance().getVertex()[x + a];
    double temp_2 = Parser::getInstance().getVertex()[x + b];
    Parser::getInstance().getVertex()[x + a] =
        std::cos(angle - prev_angle) * temp_1 -
        std::sin(angle - prev_angle) * temp_2;
    Parser::getInstance().getVertex()[x + b] =
        std::sin(angle - prev_angle) * temp_1 +
        std::cos(angle - prev_angle) * temp_2;
  }

  if (axis == 'x') prev_angle_x = angle;
  if (axis == 'y') prev_angle_y = angle;
  if (axis == 'z') prev_angle_z = angle;
}

}  // namespace s21
