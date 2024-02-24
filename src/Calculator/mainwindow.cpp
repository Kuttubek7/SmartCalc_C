#include "mainwindow.h"

#include "qcustomplot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::concat(QString str) {
  QString text = ui->label->text();

  if (static_cast<int>(text.length()) == 1 &&
      *text.toLocal8Bit().constData() == '0' &&
      *str.toLocal8Bit().constData() != '.')
    ui->label->clear();

  ui->label->setText(ui->label->text() + str);
}

void MainWindow::on_null_2_clicked() { MainWindow::concat("0"); }

void MainWindow::on_one_clicked() { MainWindow::concat("1"); }

void MainWindow::on_two_clicked() { MainWindow::concat("2"); }

void MainWindow::on_three_clicked() { MainWindow::concat("3"); }

void MainWindow::on_four_clicked() { MainWindow::concat("4"); }

void MainWindow::on_five_clicked() { MainWindow::concat("5"); }

void MainWindow::on_six_clicked() { MainWindow::concat("6"); }

void MainWindow::on_seven_clicked() { MainWindow::concat("7"); }

void MainWindow::on_eight_clicked() { MainWindow::concat("8"); }

void MainWindow::on_nine_clicked() { MainWindow::concat("9"); }

void MainWindow::on_pushButton_15_clicked() { MainWindow::concat("."); }

void MainWindow::on_plus_clicked() { MainWindow::concat("+"); }

void MainWindow::on_minus_clicked() { MainWindow::concat("-"); }

void MainWindow::on_mult_clicked() { MainWindow::concat("*"); }

void MainWindow::on_div_clicked() { MainWindow::concat("/"); }

void MainWindow::on_mod_clicked() { MainWindow::concat("%"); }

void MainWindow::on_X_clicked() { MainWindow::concat("x"); }

void MainWindow::on_Lbracket_clicked() { MainWindow::concat("("); }

void MainWindow::on_Rbracket_clicked() { MainWindow::concat(")"); }

void MainWindow::on_pow_clicked() { MainWindow::concat("^"); }

void MainWindow::on_sqrt_clicked() { MainWindow::concat("sqrt"); }

void MainWindow::on_ln_clicked() { MainWindow::concat("ln"); }

void MainWindow::on_log_clicked() { MainWindow::concat("log"); }

void MainWindow::on_cos_clicked() { MainWindow::concat("cos"); }

void MainWindow::on_sin_clicked() { MainWindow::concat("sin"); }

void MainWindow::on_tan_clicked() { MainWindow::concat("tan"); }

void MainWindow::on_acos_clicked() { MainWindow::concat("acos"); }

void MainWindow::on_asin_clicked() { MainWindow::concat("asin"); }

void MainWindow::on_atan_clicked() { MainWindow::concat("atan"); }

void MainWindow::on_plus_minus_clicked() {
  double res = 0.;
  QString tmp;
  if (ui->plus_minus->text() == "+/-") {
    res = (ui->label->text()).toDouble();
    res *= -1;
    tmp = QString::number(res, 'g', 15);
  }
  ui->label->setText(tmp);
}

void MainWindow::on_equal_clicked() {
  QString str = ui->label->text();
  std::string strs = str.toStdString();
  const char *ptr = strs.c_str();
  int error = 0;
  error = check_input(ptr);
  QString str_x = ui->label_value->text();
  double x = str_x.toDouble();
  Node *polish = NULL;
  if (error == 0) {
    QString str_x = ui->label_value->text();
    double x = str_x.toDouble();
    Node *polish = NULL;
    polish = parsing(ptr);
    polish = polish_notation(polish, x);
    double result = calculation(polish);
    char arr[1000] = {0};
    sprintf(arr, "%0.7lf", result);
    ui->label->setText(arr);
  } else
    ui->label->setText("ERROR!");
}

void MainWindow::on_delete_2_clicked() {
  QString s = ui->label->text();
  if (s.length() > 0) {
    QString newtext = s.remove(s.length() - 1, 1);
    ui->label->setText(newtext);
  }
}

void MainWindow::on_delete_1_clicked() {
  QString s = ui->label->text();
  if (s.length() > 0) {
    QString newtext = s.remove(s.length() - s.length(), s.length());
    ui->label->setText(newtext);
  }
}

// -------DRAWWWWW-GRAFFFFFFFFFF-------------------------------------
void MainWindow::on_pushButton_draw_clicked() {
  getData();
  recountPixels();
  drawGraph(1);
}

void MainWindow::getData() {
  leftX = ui->xMin->value();
  rightX = ui->xMax->value();
  leftY = ui->yMin->value();
  rightY = ui->yMax->value();

  if (leftX >= rightX) {
    leftX = -10;
    rightX = 10;
    ui->xMin->setValue(-10);
    ui->xMax->setValue(-10);
  }
  if (leftY >= rightY) {
    leftY = -10;
    rightY = 10;
    ui->yMin->setValue(-10);
    ui->yMax->setValue(-10);
  }
}

void MainWindow::recountPixels() {
  onePixelX = 381.0 / (rightX - leftX);
  onePixelY = 281.0 / (rightY - leftY);
  Ox = fabs(leftX);
  Oy = rightY;
}

void MainWindow::drawGraph(bool notEmpty) {
  char c_str2[256] = {0};
  pictHeight = 281;
  pictWidth = 381;
  QPixmap graph(381, 281);
  QPainter paint;
  paint.begin(&graph);
  paint.eraseRect(0, 0, 381, 281);
  paint.drawLine(Ox * onePixelX, 0, Ox * onePixelX, pictHeight);
  paint.drawLine(0, Oy * onePixelY, pictWidth, Oy * onePixelY);
  paint.setPen(QPen(Qt::black, 3));

  for (double i = leftX; i <= rightX; i += 10.0)
    paint.drawPoint((i + Ox) * onePixelX, Oy * onePixelY);
  for (double i = leftY; i <= rightY; i += 10.0)
    paint.drawPoint(Ox * onePixelX, (i + Oy) * onePixelY);
  QPainterPath path;
  double step = (rightX - leftX) * 0.001;

  std::string str = ui->label->text().toStdString();
  char *ptr = &str[0];

  for (double tmp = leftX; tmp <= rightX; tmp += step) {
    Node *polish = parsing(ptr);
    x = tmp;
    polish = polish_notation(polish, tmp);
    y = calculation(polish);
    y = y * (-1.0);
    paint.drawPoint((x + Ox) * onePixelX, (y + Oy) * onePixelY);
    paint.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    paint.drawPath(path);
  }
  paint.end();
  ui->drawing_field->setPixmap(graph);
}
