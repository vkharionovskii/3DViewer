#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <iostream>
// #include <QOpenGLWidget>
#include <math.h>

#include <QDir>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QScreen>
#include <QSettings>
#include <QTextEdit>
#include <QTimer>
#include <QWheelEvent>
#include <algorithm>
#include <cstdint>
#include <vector>

#include "../GifLib/gifImage/qgifimage.h"

// #include "../controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_pushButton_openFile_clicked();

  void wheelEvent(QWheelEvent *event);

  void paintOver();

  void on_doubleSpinBox_point_size_valueChanged(double arg1);

  void on_doubleSpinBox_line_width_valueChanged(double arg1);

  void on_radioButton_circle_clicked();

  void on_radioButton_square_clicked();

  void on_radioButton_empty_clicked();

  void on_radioButton_solid_clicked();

  void on_radioButton_dash_dotted_clicked();

  void on_radioButton_dotted_clicked();

  void on_pushButton_screen_clicked();

  void exposeConditionWidget();

  void on_doubleSpinBox_zoom_valueChanged(double arg1);

  void on_doubleSpinBox_move_x_valueChanged(double arg1);

  void on_doubleSpinBox_move_y_valueChanged(double arg1);

  void on_doubleSpinBox_move_z_valueChanged(double arg1);

  void on_doubleSpinBox_xRot_valueChanged(double arg1);

  void on_doubleSpinBox_yRot_valueChanged(double arg1);

  void on_doubleSpinBox_zRot_valueChanged(double arg1);

  void on_pushButton_hide_show_all_clicked();

  void hide_show_all(bool visible);

  void on_pushButton_gif_clicked();

  void createScreen();

  void saveGif();

  void on_pushButton_reset_clicked();

  void on_pushButton_frustum_clicked();

  void on_pushButton_ortho_clicked();

 private:
  Ui::View *ui;
  bool openFile_ = false;
  QVector<QImage> gif_;
  QTimer *timer_;
  int record_gif_ = 0;
  double time_ = 0.0;

  void checkOpenFile();
  void setInfoModel(std::string &pathFile);
};
}  // namespace s21

#endif  // VIEW_H
