#include <yatt/mainwindow.hpp>
#include <yatt/renderwidget.hpp>
#include <yatt/ui.hpp>

#include <QGridLayout>
#include <QMainWindow>
#include <QScreen>
#include <QWidget>

/**
 * @brief MainWindow::MainWindow creates the main window of the application
 * @param parent is the parent widget
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // set initial window size
  this->resize(ui::SCREEN_RATIO * this->screen()->size());

  // set main window name
  this->setWindowTitle(ui::MAINWINDOW_NAME);

  // use central widget as global container
  QWidget *container = new QWidget(this);
  this->setCentralWidget(container);
  QGridLayout *layout = new QGridLayout(container);
  layout->setSpacing(0);
  layout->setMargin(0);

  // create widgets
  RenderWidget *renderWidget = new RenderWidget(this);

  // add widgets to layout
  layout->addWidget(renderWidget, 0, 0, 1, 1);
}

/**
 * @brief MainWindow::~MainWindow destructs the main window of the application
 */
MainWindow::~MainWindow() {}
