#include "colorpalette.h"

#include <QDir>
#include <iostream>

s21::ColorPalette::ColorPalette(QWidget *parent) : QLabel(parent) {
  setAutoFillBackground(true);
  QPalette pal;

  //    QDir dir(SRCDIR);

  QPixmap pix(":/pallete/color_map.png");

  //    QString s;
  //    s = dir.path();
  //    s = dir.relativeFilePath("color_map.png");
  //    qDebug() << dir.currentPath();

  setMask(pix.mask());
  pal.setBrush(backgroundRole(), QBrush(pix));
  setPalette(pal);
  resize(pix.size());
}

void s21::ColorPalette::mousePressEvent(QMouseEvent *e) {
  QRect onePixRect(e->pos(), QSize(1, 1));
  QPixmap pix = grab(onePixRect);
  QImage img = pix.toImage();
  QColor color(img.pixel(0, 0));

  r = color.redF();
  g = color.greenF();
  b = color.blueF();

  std::cout << color.redF() << std::endl;
  std::cout << color.greenF() << std::endl;
  std::cout << color.blueF() << std::endl;
  emit clicked();
}
