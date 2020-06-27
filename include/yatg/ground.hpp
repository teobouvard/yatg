#pragma once

#include <QComponent>
#include <QEntity>
#include <QMesh>
#include <QObject>
#include <QVector3D>
#include <Qt3DRender>

/**
 * @brief The Ground class represents the ground object
 */
class Ground : public Qt3DCore::QEntity {
  Q_OBJECT
public:
  Ground(Qt3DCore::QNode *parent = nullptr);

signals:
  void centerChanged(QVector3D);

public slots:
  void connectGeometry();
  void computeCenter();
  void printSource(const QUrl &source);

private:
  Qt3DRender::QMesh *mesh_;
};
