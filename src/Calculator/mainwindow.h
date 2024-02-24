#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QWidget>
#include <QtGui>

#include "qcustomplot.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "calc.h"
#ifdef __cpluplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  double x, y;
  void drawGraph(
      bool notEmpty = 0);  // функция, отвечающая за отрисовку графика
  void recountPixels();  // в зависимости от точности (об этом позже) считаем
                         // количество пикселей на один условный сантиметр
  void getData();  // получаем значения границ графика и точности

 private:
  Ui::MainWindow *ui;
  double leftX, rightX;       // границы по х
  double leftY, rightY;       // границы по у
  int pictWidth, pictHeight;  // ширина и высота картинки
  double step;                // шаг (точность)
  double onePixelX, onePixelY;  // количество пикселей на шаг
  double Ox, Oy;                // координаты центра

 private slots:
  void on_delete_2_clicked();  // удаляет по одной
  void on_delete_1_clicked();  // удаляет всю строку
  void on_null_2_clicked();
  void concat(QString str);
  void on_one_clicked();
  void on_two_clicked();
  void on_three_clicked();
  void on_four_clicked();
  void on_five_clicked();
  void on_six_clicked();
  void on_seven_clicked();
  void on_eight_clicked();
  void on_nine_clicked();
  void on_pushButton_15_clicked();
  void on_plus_clicked();
  void on_minus_clicked();
  void on_mult_clicked();
  void on_div_clicked();
  void on_mod_clicked();
  void on_X_clicked();
  void on_Lbracket_clicked();
  void on_Rbracket_clicked();
  void on_pow_clicked();
  void on_sqrt_clicked();
  void on_ln_clicked();
  void on_log_clicked();
  void on_cos_clicked();
  void on_sin_clicked();
  void on_tan_clicked();
  void on_acos_clicked();
  void on_asin_clicked();
  void on_atan_clicked();
  void on_plus_minus_clicked();
  void on_equal_clicked();
  void on_pushButton_draw_clicked();
};
#endif  // MAINWINDOW_H
