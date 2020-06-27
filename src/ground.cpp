#include <yatg/ground.hpp>

#include <QEntity>
#include <QMesh>
#include <QNode>
#include <QObject>
#include <QPhongMaterial>
#include <QPlaneMesh>
#include <QTransform>
#include <QUrl>
#include <QVector3D>
#include <Qt3DRender>

/**
 * @brief Ground::Ground creates a ground entity
 * @param parent is the parent node
 */
Ground::Ground(Qt3DCore::QNode *parent) : Qt3DCore::QEntity(parent) {
  // mesh
  mesh_ = new Qt3DRender::QMesh(this);
  mesh_->setSource(
      QUrl::fromLocalFile("/home/arthurdent/dev/yatg/assets/terrain.stl"));
  QObject::connect(mesh_, SIGNAL(statusChanged(Status)), this,
                   SLOT(connectGeometry()));

  // plane mesh transform
  Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform(this);
  planeTransform->setScale(1.0f);
  // planeTransform->setRotation(
  //    QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
  // planeTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

  // material
  Qt3DExtras::QPhongMaterial *planeMaterial =
      new Qt3DExtras::QPhongMaterial(this);
  planeMaterial->setDiffuse(QColor("grey"));

  // create entity
  this->addComponent(mesh_);
  this->addComponent(planeMaterial);
  this->addComponent(planeTransform);
}

void Ground::printSource(const QUrl &source) { qDebug() << source; }

void Ground::computeCenter() {
  auto geometry = mesh_->geometry();
  auto min = geometry->minExtent();
  auto max = geometry->maxExtent();
  auto center = (min + max) / 2.0;
  emit centerChanged(center);
  // qDebug("Center : %d %d %d", center.x(), center.y(), center.z());
  qDebug() << center.x() << center.y() << center.z();
}

void Ground::connectGeometry() {
  if (mesh_->status() == Qt3DRender::QMesh::Ready) {
    connect(mesh_->geometry(), SIGNAL(minExtentChanged(const QVector3D &)),
            this, SLOT(computeCenter()));
    connect(mesh_->geometry(), SIGNAL(maxExtentChanged(const QVector3D &)),
            this, SLOT(computeCenter()));
  }
}
