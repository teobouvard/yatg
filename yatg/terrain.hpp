#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>

class Terrain {
public:
  Terrain(int size);
  void draw(QOpenGLShaderProgram *program);

private:
  QOpenGLBuffer b_vertices;
  QOpenGLBuffer b_indices;

  QVector<QVector3D> m_grid;
  QVector<QVector3D> m_indices;
};
