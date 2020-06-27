#pragma once

#include <yatt/renderwidget.hpp>

#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  virtual ~MainWindow();

private:
};
