#include "yatg/openglwindow.hpp"
#include "yatg/vertex.hpp"
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QString>

// Create a colored triangle
static const Vertex tri_vertexes[] = {
    Vertex(QVector3D(0.00f, 0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)),
    Vertex(QVector3D(0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)),
    Vertex(QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f))};

OpenGLWindow::OpenGLWindow() {}

OpenGLWindow::~OpenGLWindow() {
  makeCurrent();
  m_object.destroy();
  m_vertex.destroy();
  delete m_program;
}

void OpenGLWindow::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  printContext();

  // Application-specific initialization
  {
    // Create shader (Do not release until VAO is created)
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                       ":/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/shaders/simple.frag");
    m_program->link();
    m_program->bind();

    // Create Buffer (Do not release until VAO is created)
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(tri_vertexes, sizeof(tri_vertexes));

    // Create Vertex Array Object
    m_object.create();
    m_object.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(),
                                  Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(),
                                  Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    m_object.release();
    m_vertex.release();
    m_program->release();
  }
}

void OpenGLWindow::resizeGL(int w, int h) {
  (void)w;
  (void)h;
}

void OpenGLWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT); // Render using our shader
  m_program->bind();
  {
    m_object.bind();
    glDrawArrays(GL_TRIANGLES, 0,
                 sizeof(tri_vertexes) / sizeof(tri_vertexes[0]));
    m_object.release();
  }
  m_program->release();
}

void OpenGLWindow::printContext() {
  QString gl_type;
  QString gl_version;
  QString gl_profile;

  // Get version nformation
  gl_type = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  gl_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));

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
