#include "mainwindow.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // this->setStyleSheet("background-color: gray;");
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
  ui->openGLWidget->setRotation(dxRotation, dyRotation, true);
  // qDebug() << QString::number(event->pos().x()) << " " << QString::number(event->pos().y());
  //
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  // if (event->button() == Qt::LeftButton) event->ignore();
  if (event->button() == Qt::RightButton) {
	isRotationEnable = true;
	// qDebug() << isRotationEnable;
  }
  if (event->button() == Qt::MidButton) {
	ui->openGLWidget->setDefaulZoom();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
  // if (event->button() == Qt::LeftButton) event->ignore();
  if (event->button() == Qt::RightButton) {
	isRotationEnable = false;
	isStartRotation = false;
	ui->openGLWidget->setRotation(dxRotation, dyRotation, false);
	//  qDebug() << isStartRotation;
  }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
	case Qt::Key_W:
	  ui->openGLWidget->setWASDUD(FORWARD, true);
	  break;
	case Qt::Key_S:
	  ui->openGLWidget->setWASDUD(BACK, true);
	  break;
	case Qt::Key_D:
	  ui->openGLWidget->setWASDUD(RIGHT, true);
	  break;
	case Qt::Key_A:
	  ui->openGLWidget->setWASDUD(LEFT, true);
	  break;
	case Qt::Key_Space:
	  ui->openGLWidget->setWASDUD(UP, true);
	  break;
	case Qt::Key_Shift:
	  ui->openGLWidget->setWASDUD(DOWN, true);
	  break;
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  switch (event->key()) {
	case Qt::Key_W:
	  ui->openGLWidget->setWASDUD(FORWARD, false);
	  break;
	case Qt::Key_S:
	  ui->openGLWidget->setWASDUD(BACK, false);
	  break;
	case Qt::Key_D:
	  ui->openGLWidget->setWASDUD(RIGHT, false);
	  break;
	case Qt::Key_A:
	  ui->openGLWidget->setWASDUD(LEFT, false);
	  break;
	case Qt::Key_Space:
	  ui->openGLWidget->setWASDUD(UP, false);
	  break;
	case Qt::Key_Shift:
	  ui->openGLWidget->setWASDUD(DOWN, false);
	  break;
  }
}

void MainWindow::wheelEvent(QWheelEvent* event) {
  if (event->angleDelta().y() > 0) {
	ui->openGLWidget->setZoom(1.0);
	return;
  }
  if (event->angleDelta().y() < 0) {
	ui->openGLWidget->setZoom(-1.0);
	return;
  }
}
