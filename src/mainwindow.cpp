#include <yatg/mainwindow.hpp>
#include <yatg/renderwidget.hpp>
#include <yatg/ui.hpp>

#include <QGridLayout>
#include <QMainWindow>
#include <QScreen>
#include <QWidget>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // set initial window size
  this->resize(ui::SCREEN_RATIO * this->screen()->size());

  // set main window name
  this->setWindowTitle(ui::MAINWINDOW_NAME);

  // use central widget as global container
  container_ = new QWidget(this);
  layout_ = new QGridLayout(container_);
  this->setCentralWidget(container_);

  // create widgets
  renderWidget_ = new RenderWidget(this);

  // add widgets to layout
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
  delete layout_;

  delete container_;
  delete renderWidget_;
}
