#include <QApplication>

#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::View w;
  w.show();
  setlocale(LC_NUMERIC, "C");
  return a.exec();
}
