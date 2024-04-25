#include "mainscene.hpp"

MainScene::MainScene(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions() {
  // Create an OpenGL context

  // Setup scene and render it
  // initializeGL();
  // paintGL();
  // connect(&shaderTimer, shaderTimer.timeout(), this, shaderTimeShift());
}

MainScene::~MainScene() {}

void MainScene::setRotation(int _dx, int _dy) {
  dxRotation = _dx;
  dyRotation = _dy;
}

void MainScene::initializeGL() {
  initializeOpenGLFunctions();
  // Set up the rendering context, load shaders and other resources, etc.:
  // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  // f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // f->glEnable(GL_DEPTH_TEST);  // буффер глубины
  // f->glEnable(GL_CULL_FACE);   // отсечение задних граней (чтобы не рисовались)

  testProgram.create();
  if (!testProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/TestFrag.fsh")) {
	qDebug() << "Компиляции шейдера НЕуспешна";
	close();
  } else {
	qDebug() << "Компиляции шейдера успешна";
  }
  if (!testProgram.link()) {
	qDebug() << "Линковка программы НЕуспешна";
	close();
  } else {
	qDebug() << "Линковка программы успешна";
  }
  testProgram.bind();

  frameTimer = new QTimer();
  connect(frameTimer, SIGNAL(timeout()), this, SLOT(update()));
  frameTimer->start(1000 / 60);
  // glUseProgram ()
  //  QOpenGL
  //   glEnable(GL_DEPTH_TEST);  // буффер глубины
  //   glEnable(GL_CULL_FACE);   // отсечение задних граней (чтобы не рисовались)
}

void MainScene::resizeGL(int w, int h) {
  windowSizeY = h;
  windowSizeX = w;
  // Update projection matrix and other size related settings:
  // float aspect = w / (float)h;
  // m_projection.setToIdentity();
  // m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void MainScene::paintGL() {
  shaderTime += shaderdTime;

  // Draw the scene:
  // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  // QOpenGLFunctions* f = QOpenGLContext::currentContext ()->
  // f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(testProgram.programId());

  // glEnable(true);rotate
  glUniform1f(glGetUniformLocation(testProgram.programId(), "iTime"), shaderTime);
  glUniform2f(glGetUniformLocation(testProgram.programId(), "iResolution"), (double)windowSizeX, (double)windowSizeY);
  glUniform2f(glGetUniformLocation(testProgram.programId(), "iRotate"), (double)dxRotation, (double)dyRotation);

  glBegin(GL_TRIANGLE_FAN);
  // glColor3f(1.0, 1.0, 1.0);
  glVertex2f(-1.0, -1.0);
  glVertex2f(-1.0, 1.0);
  glVertex2f(1.0, 1.0);
  glVertex2f(1.0, -1.0);
  glEnd();
  //      glUseProgram(0);
  //       create();
  //        testProgram.release();
  //         glUseProgram(testProgram);
  //          QOpenGLDraw
  //           glPushMatrix();
}
