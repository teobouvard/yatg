#pragma once
#include "yatg/transform3d.hpp"
#include <QMatrix4x4>
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

protected slots:
  void update();

private:
  // OpenGL state information
  QOpenGLBuffer m_vertex;
  QOpenGLVertexArrayObject m_object;
  QOpenGLShaderProgram *m_program;

  // Shader Information
  int u_modelToWorld;
  int u_worldToView;
  QMatrix4x4 m_projection;
  Transform3D m_transform;

  // Private debug helper
  void printContext();
};
