#pragma once

#include <yatg/renderwidget.hpp>

#include <QGridLayout>
#include <QMainWindow>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  virtual ~MainWindow();

private:
  QGridLayout *layout_;

  // widgets
  QWidget *container_;
  RenderWidget *renderWidget_;
};
