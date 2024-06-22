#ifndef SCENE_H
#define SCENE_H

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QSettings>
#include <QtOpenGL>

// #include "view.h"

#define PATH $PWD

namespace s21 {

class scene : public QOpenGLWidget {
  Q_OBJECT

 public:
  scene(QWidget *parent = nullptr);
  ~scene();

  double xRot, yRot, zRot;
  double xRot_m, yRot_m, zRot_m;
  double move_x = 0.0, move_y = 0.0, move_z = 0.0;
  double zoom = 1.0;
  double rgb[9];
  QPoint mPos;
  double pointSize = 0.0, lineWidth = 0.0;
  int pointType = 0, lineType = 0;
  QSettings *settings;
  bool ortho = true;

  void recordPreferences();
  void setPreferences();

  void zooming(double arg);
  void moveXYZ(size_t axis, double value);

 private:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);

 public slots:

 signals:
  void mouseMove();
};

}  // namespace s21

#endif  // SCENE_H
