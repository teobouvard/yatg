#pragma once

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
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
  QOpenGLShaderProgram *m_program;

  // Transformations
  QMatrix4x4 projection;

  // Object data
  Terrain *m_terrain;

  // Private debug helper
  void print_context();
};
