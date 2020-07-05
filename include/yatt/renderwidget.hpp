#pragma once

#include <yatt/ground.hpp>

#include <QWidget>
#include <Qt3DWindow>

class RenderWidget : public QWidget {
  Q_OBJECT
public:
  explicit RenderWidget(QWidget *parent = nullptr);
  virtual ~RenderWidget();

protected slots:
  void viewGround();

private:
  Qt3DRender::QCamera *camera_;

  Ground *ground_;
};
