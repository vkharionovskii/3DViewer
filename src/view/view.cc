#include "view.h"

#include "../controller/controller.h"
#include "colorpalette.h"
#include "ui_view.h"

namespace s21 {

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);

  ui->widget->setPreferences();
  exposeConditionWidget();
  timer_ = new QTimer(0);
  ui->label_info->setVisible(false);

  connect(ui->widget_2, SIGNAL(clicked()), this, SLOT(paintOver()));
  connect(timer_, SIGNAL(timeout()), this, SLOT(createScreen()));
}

View::~View() { delete ui; }

void View::on_pushButton_openFile_clicked() {
  string &&pathFile =
      QFileDialog::getOpenFileName(0, tr("Open file"), "../OBJ", tr("*.obj"))
          .toStdString();

  if (openFile_ == true) {
    on_pushButton_reset_clicked();
  }

  s21::Controller::getInstance().parseFile(pathFile);
  checkOpenFile();
  setInfoModel(pathFile);
}

void View::checkOpenFile() {
  if (openFile_ == false) {
    ui->doubleSpinBox_zoom->setValue(ui->widget->zoom);

    ui->widget->moveXYZ(0, ui->widget->move_x);
    ui->widget->moveXYZ(1, ui->widget->move_y);
    ui->widget->moveXYZ(2, ui->widget->move_z);

    ui->doubleSpinBox_xRot->setValue(ui->widget->xRot);
    ui->doubleSpinBox_yRot->setValue(ui->widget->yRot);
    ui->doubleSpinBox_zRot->setValue(ui->widget->zRot);
    openFile_ = true;
  }
  ui->label_info->setVisible(true);
}
void View::setInfoModel(std::string &pathFile) {
  QLabel *l = ui->label_info;
  l->setText("Name: ");
  l->setText(l->text() + (&pathFile[0] + pathFile.find_last_of('/') + 1) +
             "\n");
  l->setText(
      l->text() + "Vertexes: " +
      QString::number(s21::Controller::getInstance().getVertex().size() / 3.0) +
      "\n");
  l->setText(
      l->text() + "Facet: " +
      QString::number(s21::Controller::getInstance().getFacet().size() / 6.0));
}

void View::wheelEvent(QWheelEvent *event) {
  ui->doubleSpinBox_zoom->setValue(ui->doubleSpinBox_zoom->value() *
                                   (event->angleDelta().y() > 0 ? 1.1 : 0.9));
}

void View::paintOver() {
  if (ui->background->isChecked()) {
    ui->widget->rgb[0] = ui->widget_2->r;
    ui->widget->rgb[1] = ui->widget_2->g;
    ui->widget->rgb[2] = ui->widget_2->b;
  } else if (ui->line->isChecked()) {
    ui->widget->rgb[3] = ui->widget_2->r;
    ui->widget->rgb[4] = ui->widget_2->g;
    ui->widget->rgb[5] = ui->widget_2->b;
  } else if (ui->point->isChecked()) {
    ui->widget->rgb[6] = ui->widget_2->r;
    ui->widget->rgb[7] = ui->widget_2->g;
    ui->widget->rgb[8] = ui->widget_2->b;
  }
}

void View::on_doubleSpinBox_zoom_valueChanged(double arg1) {
  ui->widget->zooming(1.0);
  ui->widget->zooming(arg1);
  ui->widget->zoom = arg1;
}

void View::on_doubleSpinBox_move_x_valueChanged(double arg1) {
  ui->widget->moveXYZ(0, -ui->widget->move_x);
  ui->widget->moveXYZ(0, arg1);
  ui->widget->move_x = arg1;
}

void View::on_doubleSpinBox_move_y_valueChanged(double arg1) {
  ui->widget->moveXYZ(1, -ui->widget->move_y);
  ui->widget->moveXYZ(1, arg1);
  ui->widget->move_y = arg1;
}

void View::on_doubleSpinBox_move_z_valueChanged(double arg1) {
  ui->widget->moveXYZ(2, -ui->widget->move_z);
  ui->widget->moveXYZ(2, arg1);
  ui->widget->move_z = arg1;
}

void View::on_doubleSpinBox_xRot_valueChanged(double arg1) {
  s21::Controller::getInstance().rotateXYZ('x', -ui->widget->xRot);
  s21::Controller::getInstance().rotateXYZ('x', arg1);
  ui->widget->xRot = arg1;
}

void View::on_doubleSpinBox_yRot_valueChanged(double arg1) {
  s21::Controller::getInstance().rotateXYZ('y', -ui->widget->yRot);
  s21::Controller::getInstance().rotateXYZ('y', arg1);
  ui->widget->yRot = arg1;
}

void View::on_doubleSpinBox_zRot_valueChanged(double arg1) {
  s21::Controller::getInstance().rotateXYZ('z', -ui->widget->zRot);
  s21::Controller::getInstance().rotateXYZ('z', arg1);
  ui->widget->zRot = arg1;
}

void View::on_doubleSpinBox_point_size_valueChanged(double arg1) {
  ui->widget->pointSize = arg1;
}

void View::on_doubleSpinBox_line_width_valueChanged(double arg1) {
  ui->widget->lineWidth = arg1;
}

void View::on_radioButton_empty_clicked() { ui->widget->pointType = 0; }

void View::on_radioButton_circle_clicked() { ui->widget->pointType = 1; }

void View::on_radioButton_square_clicked() { ui->widget->pointType = 2; }

void View::on_radioButton_solid_clicked() { ui->widget->lineType = 0; }

void View::on_radioButton_dash_dotted_clicked() { ui->widget->lineType = 1; }

void View::on_radioButton_dotted_clicked() { ui->widget->lineType = 2; }

void View::on_pushButton_screen_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "name", "BMP (*.bmp);; JPEG (*.jpeg);; PNG (*.png)");

  ui->pushButton_screen->setVisible(false);
  ui->pushButton_gif->setVisible(false);
  ui->pushButton_hide_show_all->setVisible(false);
  if (!ui->widget->grab().save(file)) {
    QMessageBox::warning(this, tr("Save Error"),
                         tr("The image could not be saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(file)));
  }

  ui->pushButton_screen->setVisible(true);
  ui->pushButton_gif->setVisible(true);
  ui->pushButton_hide_show_all->setVisible(true);
}

void View::exposeConditionWidget() {
  if (ui->widget->pointType == 0) {
    ui->radioButton_empty->setChecked(true);
  } else if (ui->widget->pointType == 1) {
    ui->radioButton_circle->setChecked(true);
  } else if (ui->widget->pointType == 2) {
    ui->radioButton_square->setChecked(true);
  }

  ui->doubleSpinBox_point_size->setValue(ui->widget->pointSize);
  ui->doubleSpinBox_line_width->setValue(ui->widget->lineWidth);

  if (ui->widget->lineType == 0) {
    ui->radioButton_solid->setChecked(true);
  } else if (ui->widget->lineType == 1) {
    ui->radioButton_dash_dotted->setChecked(true);
  } else if (ui->widget->lineType == 2) {
    ui->radioButton_dotted->setChecked(true);
  }

  ui->doubleSpinBox_move_x->setValue(ui->widget->move_x);
  ui->doubleSpinBox_move_y->setValue(ui->widget->move_y);
  ui->doubleSpinBox_move_z->setValue(ui->widget->move_z);
}

void View::on_pushButton_hide_show_all_clicked() {
  bool visible = false;
  if (!ui->widget_2->isVisible()) {
    visible = true;
  }

  hide_show_all(visible);
}

void View::hide_show_all(bool visible) {
  ui->pushButton_openFile->setVisible(visible);

  ui->widget_2->setVisible(visible);

  ui->doubleSpinBox_line_width->setVisible(visible);

  ui->doubleSpinBox_move_x->setVisible(visible);
  ui->doubleSpinBox_move_y->setVisible(visible);
  ui->doubleSpinBox_move_z->setVisible(visible);

  ui->doubleSpinBox_zoom->setVisible(visible);
  ui->doubleSpinBox_point_size->setVisible(visible);

  ui->radioButton_circle->setVisible(visible);
  ui->radioButton_dash_dotted->setVisible(visible);
  ui->radioButton_dotted->setVisible(visible);
  ui->radioButton_empty->setVisible(visible);
  ui->radioButton_solid->setVisible(visible);
  ui->radioButton_square->setVisible(visible);

  ui->background->setVisible(visible);
  ui->line->setVisible(visible);
  ui->point->setVisible(visible);

  ui->doubleSpinBox_xRot->setVisible(visible);
  ui->doubleSpinBox_yRot->setVisible(visible);
  ui->doubleSpinBox_zRot->setVisible(visible);

  ui->groupBox_2->setVisible(visible);
  ui->groupBox_3->setVisible(visible);
  ui->groupBox_4->setVisible(visible);

  ui->label_info->setVisible(visible);
}

void View::on_pushButton_gif_clicked() {
  ui->pushButton_hide_show_all->setVisible(false);
  ui->pushButton_gif->setVisible(false);
  ui->pushButton_screen->setVisible(false);
  time_ = 0.0;
  record_gif_ = 1;
  timer_->start(100);
}

void View::createScreen() {
  if (record_gif_ == 1 && time_ <= 5.0) {
    gif_.push_back(ui->widget->grab().toImage());
    time_ += 0.1;
    cout << time_ << endl;
  } else if (time_ > 5.0) {
    saveGif();
    timer_->stop();
    ui->pushButton_hide_show_all->setVisible(true);
    ui->pushButton_gif->setVisible(true);
    ui->pushButton_screen->setVisible(true);
  }
}

void View::saveGif() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), "gif",
      tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
  QGifImage gif;

  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = gif_.begin(); img != gif_.end(); ++img) {
    gif.addFrame(*img);
  }

  gif.save(fileName);
  gif_.clear();
}

void View::on_pushButton_reset_clicked() {
  ui->doubleSpinBox_zoom->setValue(1.0);
  ui->doubleSpinBox_move_x->setValue(0.0);
  ui->doubleSpinBox_move_y->setValue(0.0);
  ui->doubleSpinBox_move_z->setValue(0.0);

  ui->widget->xRot_m -= ui->widget->xRot_m;
  ui->widget->yRot_m -= ui->widget->yRot_m;

  ui->doubleSpinBox_xRot->setValue(0.0);
  ui->doubleSpinBox_yRot->setValue(0.0);
  ui->doubleSpinBox_zRot->setValue(0.0);

  ui->widget->settings->clear();
  ui->widget->setPreferences();
  exposeConditionWidget();
}

void View::on_pushButton_frustum_clicked() { ui->widget->ortho = false; }

void View::on_pushButton_ortho_clicked() { ui->widget->ortho = true; }

}  // namespace s21
