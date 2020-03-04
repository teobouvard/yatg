#pragma once
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>

class Terrain {
public:
  Terrain(int size);
  void draw(QOpenGLShaderProgram *program);
  void init_geometry(QOpenGLShaderProgram *program);

private:
  QVector<QVector3D> m_grid;
};
