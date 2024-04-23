#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
};

#endif  // GLWIDGET_HPP
