#include <yatt/ground.hpp>

#include <QEntity>
#include <QGoochMaterial>
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
  QUrl meshFile =
      QUrl::fromLocalFile("/home/arthurdent/dev/srtm2stl/test/tile.stl");
  // // QUrl::fromLocalFile("/home/arthurdent/Downloads/terrain.stl");
  mesh_->setSource(meshFile);
  QObject::connect(mesh_, SIGNAL(statusChanged(Status)), this,
                   SLOT(geometryStatusChanged()));

  // plane mesh transform
  auto meshTransform = new Qt3DCore::QTransform(this);
  meshTransform->setRotation(
      QQuaternion::fromAxisAndAngle(QVector3D(-1.0f, 0.0f, 0.0f), 90.0f));

  // material
  // auto material = new Qt3DExtras::QGoochMaterial(this);
  auto material = new Qt3DExtras::QPhongMaterial(this);
  material->setDiffuse(QColor("grey"));

  // create entity
  this->addComponent(mesh_);
  this->addComponent(material);
  this->addComponent(meshTransform);
}

/*
void Ground::computeCenter() {
  auto geometry = mesh_->geometry();
  auto min = geometry->minExtent();
  auto max = geometry->maxExtent();
  auto center = (min + max) / 2.0;
  emit centerChanged(center);
  qDebug("Center : %f %f %f", center.x(), center.y(), center.z());
}*/

void Ground::geometryStatusChanged() {
  switch (mesh_->status()) {
  case Qt3DRender::QMesh::None: {
    qDebug("No mesh");
    break;
  }
  case Qt3DRender::QMesh::Loading: {
    qDebug("Loading mesh");
    break;
  }
  case Qt3DRender::QMesh::Ready: {
    qDebug("Mesh loaded");
    connect(mesh_->geometry(), SIGNAL(minExtentChanged(const QVector3D &)),
            this, SIGNAL(minExtentChanged(const QVector3D &)));
    connect(mesh_->geometry(), SIGNAL(maxExtentChanged(const QVector3D &)),
            this, SIGNAL(maxExtentChanged(const QVector3D &)));
    break;
  }
  case Qt3DRender::QMesh::Error: {
    qDebug("Error loading mesh");
    break;
  }
  }
}
