#pragma once

#include <QWidget>

class RenderWidget : public QWidget {
  Q_OBJECT
public:
  explicit RenderWidget(QWidget *parent = nullptr);
};
