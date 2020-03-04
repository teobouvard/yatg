#include "yatg/terrain.hpp"
#include <QVector3D>

Terrain::Terrain(int size) {
  (void)size;
  m_grid << QVector3D(0.5, 0.1, 0) << QVector3D(0.1, 0.9, 0)
         << QVector3D(0.9, 0.9, 0);
}

void Terrain::init_geometry(QOpenGLShaderProgram *program) {
  program->setAttributeArray("vertex", m_grid.constData());
}

void Terrain::draw(QOpenGLShaderProgram *program) {
  program->enableAttributeArray("vertex");
  glDrawArrays(GL_TRIANGLES, 0, m_grid.size());
  program->disableAttributeArray("vertex");
}
