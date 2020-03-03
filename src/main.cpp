#include "yatg/openglwindow.hpp"

#ifndef QT_DEBUG
#include <QDebug>
#endif

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Set OpenGL Version information
  // Note: This format must be set before show() is called.
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(3, 3);

  OpenGLWindow w;
  w.setFormat(format);
  w.resize(QSize(800, 600));
  w.show();
  return a.exec();
}
