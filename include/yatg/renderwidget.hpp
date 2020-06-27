#pragma once

#include <yatg/ground.hpp>

#include <QWidget>
#include <Qt3DWindow>

class RenderWidget : public QWidget {
  Q_OBJECT
public:
  explicit RenderWidget(QWidget *parent = nullptr);
  virtual ~RenderWidget();

private:
  Ground *ground_;
};
