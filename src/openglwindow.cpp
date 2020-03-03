#include "yatg/openglwindow.hpp"
#include <QDebug>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QString>

OpenGLWindow::OpenGLWindow() {
  m_terrain = new Terrain(100);
  m_program = new QOpenGLShaderProgram();

  m_projection.translate(0, 0, -5);

  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

OpenGLWindow::~OpenGLWindow() {
  makeCurrent();
  delete m_terrain;
  delete m_program;
}

void OpenGLWindow::initializeGL() {
  print_context();

  init_shaders();
  init_gl_options();
}

void OpenGLWindow::init_shaders() {
  // Add vertex and fragment shaders
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                     ":/shaders/simple.vert");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                     ":/shaders/simple.frag");
  // Compile and link shaders, fail loudly
  assert(m_program->link());
  assert(m_program->bind());
}

void OpenGLWindow::init_gl_options() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void OpenGLWindow::resizeGL(int w, int h) {
  (void)w;
  (void)h;
}

// void OpenGLWindow::update() { update(); }

void OpenGLWindow::paintGL() {
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set modelview-projection matrix
  m_program->setUniformValue("mvp_matrix", m_projection);

  // Draw cube geometry
  m_terrain->draw(m_program);
}

void OpenGLWindow::print_context() {
  QString gl_type;
  QString gl_version;
  QString gl_profile;

  // Get version nformation
  gl_type = context()->isOpenGLES() ? "OpenGL ES" : "OpenGL";
  gl_version = (char *)glGetString(GL_VERSION);

  // Get Profile Information
  switch (format().profile()) {
  case QSurfaceFormat::NoProfile:
    gl_profile = "No Profile";
    break;
  case QSurfaceFormat::CoreProfile:
    gl_profile = "Core Profile";
    break;
  case QSurfaceFormat::CompatibilityProfile:
    gl_profile = "Compatibility Profile";
    break;
  default:
    gl_profile = "Unknown Profile";
  }

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(gl_type) << qPrintable(gl_version) << "("
           << qPrintable(gl_profile) << ")";
}
