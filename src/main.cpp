#include <yatt/mainwindow.hpp>

#include <QtWidgets>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow w;
  w.show();
  return app.exec();
}
