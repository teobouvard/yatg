#pragma once
#include <QOpenGLShaderProgram>
#include <QVector>

class Terrain {
public:
  Terrain(int size);
  void draw(QOpenGLShaderProgram *program);

private:
  int m_size;
  QVector<QVector<int>> m_grid;
};
