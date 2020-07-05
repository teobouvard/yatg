#include <yatt/renderwidget.hpp>

#include <igclib/race.hpp>

#include <QCamera>
#include <QColor>
#include <QDebug>
#include <QDirectionalLight>
#include <QEntity>
#include <QFirstPersonCameraController>
#include <QForwardRenderer>
#include <QGridLayout>
#include <QOrbitCameraController>
#include <QPointLight>
#include <QRgb>
#include <QString>
#include <QTorusMesh>
#include <QTransform>
#include <QVector3D>
#include <QWidget>

/**
 * @brief RenderWidget::RenderWidget
 * @param parent
 */
RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent) {
  auto rootEntity = new Qt3DCore::QEntity();
  auto view = new Qt3DExtras::Qt3DWindow(this->screen());
  view->setRootEntity(rootEntity);
  view->defaultFrameGraph()->setClearColor(QColor("gray"));
  QWidget *container = QWidget::createWindowContainer(view);

  // ground
  ground_ = new Ground(rootEntity);

  std::string task =
      "/home/arthurdent/dev/igclib/tests/data/task/xctrack_1.xctsk";
  std::string flights = "/home/arthurdent/dev/igclib/tests/data/race/1_all";
  // Race race(flights, task);

  // camera
  // TODO package different cameras
  double fov = 90.0;
  double aspect = 16.0 / 9.0;
  double near = 0.1;
  double far = 10000.0;
  camera_ = view->camera();
  camera_->lens()->setPerspectiveProjection(fov, aspect, near, far);
  camera_->setPosition(QVector3D(0, 1000, 0));
  // connect(ground_, SIGNAL(centerChanged(QVector3D)), cameraEntity,
  // SLOT(setPosition(QVector3D)));
  // connect(ground_, SIGNAL(centerChanged(QVector3D)), cameraEntity,
  //        SLOT(setViewCenter(QVector3D)));
  // QObject::connect(ground_, SIGNAL(centerChanged(QVector3D)), this,
  // SLOT(viewGround()));

  // camera controls
  auto *camController =
      new Qt3DExtras::QFirstPersonCameraController(rootEntity);
  camController->setLinearSpeed(camController->linearSpeed() * 100);
  camController->setCamera(camera_);

  // light
  // TODO package as Sun
  Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
  auto *light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(2);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(QVector3D(0, 1000, 0));
  lightEntity->addComponent(lightTransform);

  // widget layout
  auto layout_ = new QGridLayout(this);
  layout_->setMargin(0);
  layout_->setSpacing(0);
  this->setLayout(layout_);
  layout_->addWidget(container, 0, 0, 1, 1);
}

void RenderWidget::viewGround() {
  camera_->viewEntity(ground_);
  camera_->tiltAboutViewCenter(20);
}

/**
 * @brief RenderWidget::~RenderWidget
 */
RenderWidget::~RenderWidget() {}
