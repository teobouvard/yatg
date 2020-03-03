#include "yatg/openglwindow.hpp"
#include "yatg/vertex.hpp"
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QString>

// Front Vertices
#define VERTEX_FTR                                                             \
  Vertex(QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f, 0.0f))
#define VERTEX_FTL                                                             \
  Vertex(QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 1.0f, 0.0f))
#define VERTEX_FBL                                                             \
  Vertex(QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(0.0f, 0.0f, 1.0f))
#define VERTEX_FBR                                                             \
  Vertex(QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 0.0f, 0.0f))

// Back Vertices
#define VERTEX_BTR                                                             \
  Vertex(QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f, 0.0f))
#define VERTEX_BTL                                                             \
  Vertex(QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(0.0f, 1.0f, 1.0f))
#define VERTEX_BBL                                                             \
  Vertex(QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f, 1.0f))
#define VERTEX_BBR                                                             \
  Vertex(QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f, 1.0f))

// Create a colored cube
static const Vertex tri_vertexes[] = {
    // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL, VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
    // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR, VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
    // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL, VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
    // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL, VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
    // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL, VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
    // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR, VERTEX_BBR, VERTEX_BTR, VERTEX_FTR};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

OpenGLWindow::OpenGLWindow() { m_transform.translate(0.0f, 0.0f, -5.0f); }

OpenGLWindow::~OpenGLWindow() {
  makeCurrent();
  m_object.destroy();
  m_vertex.destroy();
  delete m_program;
}

void OpenGLWindow::initializeGL() {
  // Set GL global info
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Debug info
  printContext();

  // Add update signal
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

  // Application-specific initialization
  {
    // Create shader (Do not release until VAO is created)
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                       ":/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/shaders/simple.frag");
    m_program->link();
    m_program->bind();

    // Cache Uniform Locations
    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToView = m_program->uniformLocation("worldToView");

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
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, w / h, 0.0f, 1000.0f);
}

void OpenGLWindow::update() {
  // Update instance information
  m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

  // Schedule a redraw
  QOpenGLWindow::update();
}

void OpenGLWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT); // Render using our shader
  m_program->bind();
  m_program->setUniformValue(u_worldToView, m_projection);
  {
    m_object.bind();
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
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
