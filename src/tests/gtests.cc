#include "gtests.h"

TEST_F(Test, ParseFile) {
  ASSERT_DOUBLE_EQ(parser.getVertex().size() / 3.0, 8);
  ASSERT_DOUBLE_EQ(parser.getFacet().size() / 6.0, 12);
}

TEST_F(Test, TransformMove) {
  vector<double> vertex = s21::Parser::getInstance().getVertex();
  s21::Transform::getInstance().moveXYZ(1.0, 3.0, 2.5);

  for (size_t i = 0; i < vertex.size(); ++i) {
    if (i % 3 == 0) {
      vertex[i] += 1.0;
    } else if (i % 3 == 1) {
      vertex[i] += 3.0;
    } else if (i % 3 == 2) {
      vertex[i] += 2.5;
    }
  }

  ASSERT_TRUE(vertex == s21::Parser::getInstance().getVertex());
}

TEST_F(Test, TransformZoom) {
  ASSERT_DOUBLE_EQ(s21::Transform::getInstance().scale(zoom), zoom);
}

TEST_F(Test, TransformRotate) {
  s21::Transform::getInstance().rotateXYZ('x', 125.2);
  s21::Transform::getInstance().rotateXYZ('y', 12.2);
  s21::Transform::getInstance().rotateXYZ('z', 87.2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
