#include <yatt/renderwidget.hpp>

#include <QGridLayout>

#include <QCamera>
#include <QColor>
#include <QDebug>
#include <QDirectionalLight>
#include <QEntity>
#include <QFirstPersonCameraController>
#include <QForwardRenderer>
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

  // camera
  // TODO package different cameras
  double fov = 90.0;
  double aspect = 16.0 / 9.0;
  double near = 0.1;
  double far = 1000.0;
  Qt3DRender::QCamera *cameraEntity = view->camera();
  cameraEntity->lens()->setPerspectiveProjection(fov, aspect, near, far);
  // cameraEntity->setPosition(QVector3D(100, 100, 15));
  connect(ground_, SIGNAL(centerChanged(QVector3D)), cameraEntity,
          SLOT(setPosition(QVector3D)));

  // camera controls
  auto *camController =
      new Qt3DExtras::QFirstPersonCameraController(rootEntity);
  camController->setCamera(cameraEntity);

  // light
  // TODO package as Sun
  Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
  auto *light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(2);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  // widget layout
  QGridLayout *layout_ = new QGridLayout(this);
  layout_->setMargin(0);
  layout_->setSpacing(0);
  this->setLayout(layout_);
  layout_->addWidget(container, 0, 0, 1, 1);
}

/**
 * @brief RenderWidget::~RenderWidget
 */
RenderWidget::~RenderWidget() {}
