#include "yatg/openglwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Set OpenGL Version information
  // Note: This format must be set before show() is called.s
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(3, 3);

  OpenGLWindow w;
  w.setFormat(format);
  w.resize(800, 600);
  w.show();

  return a.exec();
}
