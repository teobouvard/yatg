#pragma once
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>
#include <yatg/terrain.hpp>

class OpenGLWindow : public QOpenGLWindow {
  Q_OBJECT
public:
  OpenGLWindow();
  ~OpenGLWindow();

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  // protected slots:
  // void update();
private:
  void init_shaders();
  void init_gl_options();

private:
  // OpenGL state information
  QOpenGLBuffer m_vertex;
  QOpenGLVertexArrayObject m_object;
  QOpenGLShaderProgram *m_program;

  // Transformations
  QMatrix4x4 m_projection;

  // Object data
  Terrain *m_terrain;

  // Private debug helper
  void print_context();
};
