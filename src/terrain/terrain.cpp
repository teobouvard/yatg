#include "yatg/terrain.hpp"
#include <QOpenGLBuffer>
#include <QVector3D>

Terrain::Terrain(int size) : b_indices(QOpenGLBuffer::IndexBuffer) {
  b_vertices.create();
  // b_indices.create();

  for (int j = 0; j < size; ++j) {
    for (int i = 0; i < size; ++i) {
      float x = (float)i / (float)size;
      float y = (float)j / (float)size;
      float z = 0.2;
      m_grid.push_back(QVector3D(x, y, z));
    }
  }
  /*
    for (int j = 0; j < size; ++j) {
      for (int i = 0; i < size; ++i) {
        int row1 = j * (size + 1);
        int row2 = (j + 1) * (size + 1);

        // triangle 1
        m_indices.push_back(QVector3D(row1 + i, row1 + i + 1, row2 + i + 1));

        // triangle 2
        m_indices.push_back(QVector3D(row1 + i, row2 + i + 1, row2 + i));
      }
    }
  */

  // Transfer vertex data to VBO 0
  b_vertices.bind();
  b_vertices.allocate(m_grid.constData(), m_grid.size() * sizeof(QVector3D));

  // Transfer index data to VBO 1
  // b_indices.bind();
  // b_indices.allocate(m_indices.constData(),
  //                   m_indices.size() * sizeof(QVector3D));
  // m_buffer.release();
}

void Terrain::draw(QOpenGLShaderProgram *program) {
  b_vertices.bind();
  b_indices.bind();

  quintptr offset = 0;

  int v_position = program->attributeLocation("v_position");
  program->enableAttributeArray(v_position);
  program->setAttributeBuffer(v_position, GL_FLOAT, offset, 3,
                              sizeof(QVector3D));
  glDrawElements(GL_TRIANGLE_STRIP, m_indices.size() * 3, GL_UNSIGNED_INT,
                 NULL);
}
