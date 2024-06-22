#ifndef COLORPALETTE_H_
#define COLORPALETTE_H_

#include <QBitmap>
#include <QDebug>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <QWidget>

namespace s21 {

class ColorPalette : public QLabel {
  Q_OBJECT
 public:
  explicit ColorPalette(QWidget *parent = 0);
  double r = 0, g = 0, b = 0;

 signals:
  void Color(QColor color);
  void clicked();

 public slots:
  virtual void mousePressEvent(QMouseEvent *e);
};

}  // namespace s21

#endif  // COLORPALETTE_H_
