#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP
// #pragma comment(lib, "opengl32.lib")

// in to RPO: LIBS += -LC:\Qt\5.12.12\mingw73_64\lib\libQt5OpenGL.a -lopengl32
#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>

class MainScene : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  MainScene(QWidget* parent = 0);
  ~MainScene();
  void setRotation(int _dx, int _dy);

 protected:
  void initializeGL() override;

  void resizeGL(int w, int h) override;

  void paintGL() override;

 private:
  bool isRotationEnable = false;
  int dxRotation = 0;
  int dyRotation = 0;
  int windowSizeY = 0;
  int windowSizeX = 0;
  // const char* testShader;
  // GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
  // GLuint program = glCreateProgram();
  QOpenGLShaderProgram testProgram;
  float shaderTime = 0.0f;
  float shaderdTime = 0.05f;
  QTimer* frameTimer;

  // QOpenGLFramebufferObject framebuffer;
};

#endif  // MAINSCENE_HPP
