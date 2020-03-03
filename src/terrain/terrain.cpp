#include "yatg/terrain.hpp"
#include <QVector3D>

Terrain::Terrain(int size) {
  m_size = size;
  for (int i = 0; i < m_size; i++) {
    m_grid.push_back(QVector<int>());
    for (int j = 0; j < m_size; j++) {
      m_grid.back().push_back(0);
    }
  }
}

void Terrain::draw(QOpenGLShaderProgram *program) { (void)program; }
