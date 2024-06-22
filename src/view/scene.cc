#include "scene.h"

#include "../controller/controller.h"

namespace s21 {

scene::scene(QWidget *parent) : QOpenGLWidget(parent) {
  settings =
      new QSettings(QCoreApplication::applicationDirPath() + "/settings.conf",
                    QSettings::IniFormat);
}

scene::~scene() { delete settings; }

void scene::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(rgb[0], rgb[1], rgb[2], 1.0);

  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
}

void scene::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void scene::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  vector<double> &vertex = s21::Controller::getInstance().getVertex();
  vector<unsigned int> &facet = s21::Controller::getInstance().getFacet();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (!ortho) {
    glFrustum(-scene::width(), scene::width(), -scene::height(),
              scene::height(), 700, 10000);
    glTranslated(0, 0, -700.0 * 3.0);
  } else {
    glOrtho(-scene::width(), scene::width(), -scene::height(), scene::height(),
            -10000, 10000);
    glScaled(1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotated(xRot_m, 1.0, 0.0, 0.0);
  glRotated(yRot_m, 0.0, 1.0, 0.0);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_DOUBLE, 0, &vertex[0]);

  glLineWidth(lineWidth);

  if (pointType == 1) {
    glEnable(GL_POINT_SMOOTH);
  }

  glClearColor(rgb[0], rgb[1], rgb[2], 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_LINE_STIPPLE);

  if (lineType == 1) {
    glLineStipple(2, 0X11FF);
  } else if (lineType == 2) {
    glLineStipple(2, 0X00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glColor3d(rgb[3], rgb[4], rgb[5]);
  glDrawElements(GL_LINES, facet.size(), GL_UNSIGNED_INT, &facet[0]);

  if (pointType != 0) {
    glPointSize(pointSize);
    glColor3d(rgb[6], rgb[7], rgb[8]);
    glDrawElements(GL_POINTS, facet.size(), GL_UNSIGNED_INT, &facet[0]);
  }

  update();

  glDisable(GL_LINE_STIPPLE);
  glDisable(GL_POINT_SMOOTH);
  glDisableClientState(GL_VERTEX_ARRAY);

  recordPreferences();
}

void scene::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void scene::mouseMoveEvent(QMouseEvent *mo) {
  xRot_m += 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot_m += 1 / M_PI * (mo->pos().x() - mPos.x());
  mPos = mo->pos();
  update();
}

void scene::recordPreferences() {
  settings->setValue("zoom", zoom);
  settings->setValue("TypeProjection", ortho);

  settings->setValue("pointType", pointType);
  settings->setValue("pointSize", pointSize);

  settings->setValue("lineWidth", lineWidth);
  settings->setValue("lineType", lineType);

  settings->setValue("background_r", rgb[0]);
  settings->setValue("background_g", rgb[1]);
  settings->setValue("background_b", rgb[2]);

  settings->setValue("lines_r", rgb[3]);
  settings->setValue("lines_g", rgb[4]);
  settings->setValue("lines_b", rgb[5]);

  settings->setValue("point_r", rgb[6]);
  settings->setValue("point_g", rgb[7]);
  settings->setValue("point_b", rgb[8]);

  settings->setValue("moveX", move_x);
  settings->setValue("moveY", move_y);
  settings->setValue("moveZ", move_z);

  settings->setValue("xRot", xRot);
  settings->setValue("yRot", yRot);
  settings->setValue("zRot", zRot);
}

void scene::setPreferences() {
  zoom = settings->value("zoom", 1.0).toDouble();
  ortho = settings->value("TypeProjection", true).toBool();

  pointType = settings->value("pointType", 0).toInt();
  pointSize = settings->value("pointSize", 0).toInt();

  lineWidth = settings->value("lineWidth", 1).toInt();
  lineType = settings->value("lineType", 0).toInt();

  rgb[0] = settings->value("background_r", 0.0).toDouble();
  rgb[1] = settings->value("background_g", 0.0).toDouble();
  rgb[2] = settings->value("background_b", 0.0).toDouble();

  rgb[3] = settings->value("lines_r", 0.1).toDouble();
  rgb[4] = settings->value("lines_g", 0.75).toDouble();
  rgb[5] = settings->value("lines_b", 0.3).toDouble();

  rgb[6] = settings->value("point_r", 1.0).toDouble();
  rgb[7] = settings->value("point_g", 0.0).toDouble();
  rgb[8] = settings->value("point_b", 0.5).toDouble();

  move_x = settings->value("moveX", 0.0).toDouble();
  move_y = settings->value("moveY", 0.0).toDouble();
  move_z = settings->value("moveZ", 0.0).toDouble();

  xRot = settings->value("xRot", 0.0).toDouble();
  yRot = settings->value("yRot", 0.0).toDouble();
  zRot = settings->value("zRot", 0.0).toDouble();
}

void scene::zooming(double arg) { s21::Controller::getInstance().scale(arg); }

void scene::moveXYZ(size_t axis, double value) {
  double xyz[3] = {0.0};
  for (size_t i = 0; i <= axis; ++i) i == axis ? xyz[i] = value : xyz[i];
  s21::Controller::getInstance().moveXYZ(xyz[0], xyz[1], xyz[2]);
}

}  // namespace s21
