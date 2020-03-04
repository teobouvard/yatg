#include "yatg/openglwindow.hpp"
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QString>

OpenGLWindow::OpenGLWindow() {
  m_program = new QOpenGLShaderProgram();
  m_terrain = new Terrain(5);
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
  m_terrain->init_geometry(m_program);
}

void OpenGLWindow::init_shaders() {
  // Add vertex and fragment shaders
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                     ":/shaders/simple.vert");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                     ":/shaders/simple.frag");
  // Link and bind shaders, fail loudly
  assert(m_program->link());
  assert(m_program->bind());
}

void OpenGLWindow::init_gl_options() {
  // Set OpenGL options
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Set clear color to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

void OpenGLWindow::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const qreal zNear = 0.001;
  const qreal zFar = 1000.0;
  const qreal fov = 60.0;

  // Reset world projection
  projection.setToIdentity();

  // Set world perspective projection
  projection.perspective(fov, aspect, zNear, zFar);

  glViewport(0, 0, w, h);
}

// void OpenGLWindow::update() { update(); }

void OpenGLWindow::paintGL() {
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_program->bind();

  // projection : world to view
  // transfrom : model to world
  QMatrix4x4 transform;
  transform.translate(0.0, 0.0, -5.0);
  m_program->setUniformValue("mtv_matrix", projection * transform);

  // Draw terrain geometry
  m_terrain->draw(m_program);

  m_program->release();
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
