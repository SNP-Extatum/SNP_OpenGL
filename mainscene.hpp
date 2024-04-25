#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP
// #pragma comment(lib, "opengl32.lib")

// in to RPO: LIBS += -LC:\Qt\5.12.12\mingw73_64\lib\libQt5OpenGL.a -lopengl32
#define PI 3.1415926535

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>

#include "enums.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vecfunctions.hpp"

class MainScene : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  MainScene(QWidget* parent = 0);
  ~MainScene();
  void setRotation(int _dx, int _dy, bool isRotating);
  void setWASDUD(DIRECTIONS _direct, bool _status);
  void setZoom(float _dxZoom);
  void setDefaulZoom();

 protected:
  void initializeGL() override;

  void resizeGL(int w, int h) override;

  void paintGL() override;

 private:
  float sensitivity = 1.2f;
  bool isRotationEnable = false;
  vec2 dRotation = vec2(0);
  vec3 cameraDirection = vec3(0);
  vec2 windowSize = vec2(0);
  bool wasdUD[6] = {false, false, false, false, false, false};
  float cameraSpeed = 0.05f;
  vec3 cameraPosition = vec3(0.0, 0.0, 0.0);
  void setCameraPosition();
  double cameraZoom = 1.0f;
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
