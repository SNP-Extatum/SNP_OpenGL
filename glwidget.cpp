#include "glwidget.hpp"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}

GLfloat triangle_vertices[] = {
	0.0, 0.8, -0.8, -0.8, 0.8, -0, 8,
};
GLfloat triangle_colors[] = {
	0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
};

// исходник вершинного шейдера
const char* vertexShader =
	"attribute vec2 coord2d;\n"
	"attribute vec3 color;\n"
	"varying vec3 vColor;\n"
	"void main(void){\n"
	"gl_Position = vec4(coord2d.x, coord2d.y, 0.0, 1.0);\n"
	"}\n";

// исходник фрагментного шейдера
const char* fragmetShader =
	"varying vec3 vColor;\n"
	"void main(void) {\n"
	"gl_FragColor[0] = vColor.r;\n"
	"gl_FragColor[1] = vColor.g;\n"
	"gl_FragColor[2] = vColor.b;\n"
	"};\n";

GLint attributeCoord2d;
GLint atrributeColor;
GLuint program;

void GLWidget::initializeGL() { initializeOpenGLFunctions(); }

void GLWidget::paintGL() {}

void GLWidget::resizeGL(int width, int height) {}
