#include "mainwindow.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setMouseTracking(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  if (!isStartRotation) {
	startXpoint = event->pos().x();
	startYpoint = event->pos().y();
	isStartRotation = true;
	return;
  }
  dxRotation = event->pos().x() - startXpoint;
  dyRotation = event->pos().y() - startYpoint;
  // qDebug() << dxRotation << " " << dyRotation;
  ui->openGLWidget->setRotation(dxRotation, dyRotation);
  // qDebug() << QString::number(event->pos().x()) << " " << QString::number(event->pos().y());
  //
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::RightButton) {
	isRotationEnable = true;
	// qDebug() << isRotationEnable;
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::RightButton) {
	isRotationEnable = false;
	isStartRotation = false;
	// qDebug() << isStartRotation;
  }
}
