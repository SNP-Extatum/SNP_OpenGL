#include "mainscene.hpp"

MainScene::MainScene(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions() {
  // Create an OpenGL context

  // Setup scene and render it
  // initializeGL();
  // paintGL();
  // connect(&shaderTimer, shaderTimer.timeout(), this, shaderTimeShift());
}

MainScene::~MainScene() {}

void MainScene::setRotation(int _dx, int _dy, bool _isRotating) {
  if (_isRotating) {
	cameraDirection.x = dRotation.y + _dy;
	cameraDirection.y = dRotation.x + _dx;
	if (cameraDirection.x / windowSize.x * sensitivity > PI / 2) cameraDirection.x = PI / 2 * windowSize.x / sensitivity;
	if (cameraDirection.x / windowSize.x * sensitivity < -PI / 2) cameraDirection.x = -PI / 2 * windowSize.x / sensitivity;
  } else {
	dRotation.y = cameraDirection.x;
	dRotation.x = cameraDirection.y;
	vecFunctions::norm(cameraDirection);
  }
}

void MainScene::setWASDUD(DIRECTIONS _direct, bool _status) { wasdUD[_direct] = _status; }

void MainScene::setZoom(float _dxZoom) { cameraZoom *= 1.0 + _dxZoom * 0.1; }

void MainScene::setDefaulZoom() { cameraZoom = 1.0; }

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
  windowSize.y = h;
  windowSize.x = w;
  // Update projection matrix and other size related settings:
  // float aspect = w / (float)h;
  // m_projection.setToIdentity();
  // m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void MainScene::paintGL() {
  shaderTime += shaderdTime;
  // qDebug() << cameraDirection.x / windowSize.x * sensitivity << " " << cameraDirection.y / windowSize.y * sensitivity;
  setCameraPosition();
  //     Draw the scene:
  //     QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  //     QOpenGLFunctions* f = QOpenGLContext::currentContext ()->
  //     f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(testProgram.programId());

  // glEnable(true);rotate
  glUniform1f(glGetUniformLocation(testProgram.programId(), "iTime"), shaderTime);
  glUniform2f(glGetUniformLocation(testProgram.programId(), "iResolution"), (double)windowSize.x, (double)windowSize.y);
  glUniform3f(glGetUniformLocation(testProgram.programId(), "iRotate"), (double)cameraDirection.x / windowSize.x * sensitivity,
			  (double)cameraDirection.y / windowSize.y * sensitivity, (double)cameraDirection.z * sensitivity);

  glUniform3f(glGetUniformLocation(testProgram.programId(), "iCameraPos"), cameraPosition.x, cameraPosition.y, cameraPosition.z);
  // glUniform1f(glGetUniformLocation(testProgram.programId(), "iSensitivity"), sensitivity);
  glUniform1f(glGetUniformLocation(testProgram.programId(), "iZoom"), cameraZoom);

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

void MainScene::setCameraPosition() {
  vec3 cameraShift;
  float angle = cameraDirection.y / windowSize.y * sensitivity;
  cameraShift.x = ((float)wasdUD[RIGHT] - (float)wasdUD[LEFT]);
  cameraShift.y = ((float)wasdUD[UP] - (float)wasdUD[DOWN]);
  cameraShift.z = ((float)wasdUD[FORWARD] - (float)wasdUD[BACK]);
  vec3 dirTemp;
  dirTemp.x = cos(angle) * cameraShift.x - sin(angle) * cameraShift.z;
  dirTemp.z = sin(angle) * cameraShift.x + cos(angle) * cameraShift.z;
  dirTemp.y = cameraShift.y;
  cameraPosition += dirTemp * cameraSpeed;
}
