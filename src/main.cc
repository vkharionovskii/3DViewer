// #include "controller.h"
#include "singleton/singleton.h"

int main() {
  // s21::Controller::getInstance().parseFile("/home/vovakhari/Workspace/CPP4_3DViewer_v2.0-0/src/Pony_cartoon.obj");

  s21::Parser::getInstance().getFacet();
  // std::size_t i = 0;
  // for (auto item : parser.getVertex()) {
  //   ++i;
  //   cout << item << " ";
  //   if (i % 3 == 0) cout << endl;
  // }
  // cout << endl;

  // i = 0;
  // for (auto item : parser.getFacet()) {
  //   ++i;
  //   cout << item << " ";
  //   if (i % 10 == 0) cout << endl;
  // }

  // for (auto item : parser.getFac()) {
  //   i = 0;
  //   for (auto it : item) {
  //     cout << it << " ";
  //     ++i;
  //     if (i % item.size() == 0) cout << endl;
  //   }
    // if (i % 10 == 0) cout << endl;
  // }

  return 0;
}
