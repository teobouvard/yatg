QT += core gui widgets 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation

greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/ground.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/renderwidget.cpp

HEADERS += \
    include/yatg/ground.hpp \
    include/yatg/mainwindow.hpp \
    include/yatg/renderwidget.hpp \
    include/yatg/ui.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
