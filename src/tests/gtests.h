#ifndef SRC_GTEST_H_
#define SRC_GTEST_H_

#include <gtest/gtest.h>

#include "../singleton/singleton.h"

class Test : public ::testing::Test {
 protected:
  double zoom = 3.0;
  s21::Parser &parser = s21::Parser::getInstance();

 public:
  Test() { parser.parseFile("OBJ/cubeAlmaz.obj"); }
  ~Test() {}
  void SetUp() {}
  void TearDown() {}
};

#endif  // SRC_GTEST_H_
