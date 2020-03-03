#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>

class QOpenGLShaderProgram;

class OpenGLWindow : public QOpenGLWindow {
  Q_OBJECT
public:
  OpenGLWindow();
  ~OpenGLWindow();

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

private:
  // OpenGL state information
  QOpenGLBuffer m_vertex;
  QOpenGLVertexArrayObject m_object;
  QOpenGLShaderProgram *m_program;

  // Private debug helper
  void printContext();
};
