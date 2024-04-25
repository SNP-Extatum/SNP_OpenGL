#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDebug>
#include <QMainWindow>
#include <QMouseEvent>
#include <QWheelEvent>
// #include "mainscene.hpp"
#include "enums.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

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

 private:
  Ui::MainWindow *ui;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  bool isRotationEnable = false;
  bool isStartRotation = false;
  int dxRotation;
  int dyRotation;
  int startXpoint;
  int startYpoint;
};
#endif  // MAINWINDOW_HPP
