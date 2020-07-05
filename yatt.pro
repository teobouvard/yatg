QT += core gui widgets 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation

greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_FATAL_WARNINGS

INCLUDEPATH += \
    $$PWD/include \
    $$PWD/../igclib/include/
    $$PWD/../igclib/build/src/

SOURCES += \
    src/ground.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/renderwidget.cpp

HEADERS += \
    include/yatt/ground.hpp \
    include/yatt/mainwindow.hpp \
    include/yatt/renderwidget.hpp \
    include/yatt/ui.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#;win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../igclib/build/src/ -llib_igclib-d
#;else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../igclib/build/src/ -llib_igclib-dd
#;else:unix: LIBS += "-L$$PWD/../igclib/build/src/" -lliblib_igclibs
#;#else:unix: LIBS += $$PWD/../igclib/build/src/liblib_igclib-d.so

DEPENDPATH += $$PWD/../igclib/include/
