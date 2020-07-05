#pragma once

#include <QComponent>
#include <QEntity>
#include <QMesh>
#include <QObject>
#include <QVector3D>
#include <Qt3DRender>

/**
 * @brief The Ground class represents the ground elevation model
 */
class Ground : public Qt3DCore::QEntity {
  Q_OBJECT
public:
  Ground(Qt3DCore::QNode *parent = nullptr);

signals:
  void minExtentChanged(const QVector3D &);
  void maxExtentChanged(const QVector3D &);

public slots:
  void geometryStatusChanged();

private:
  Qt3DRender::QMesh *mesh_;
};
