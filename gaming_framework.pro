QT       += widgets
CONFIG   += c++14 sdk_no_version_check
TEMPLATE  = app
TARGET    = gaming_framework

QMAKE_LIBS_OPENGL = -framework OpenGL

SOURCES += \
    main.cpp \
    user.cpp \
    userdatabase.cpp \
    authmanager.cpp \
    disc.cpp \
    gamescene.cpp \
    loginscreen.cpp \
    signupscreen.cpp \
    homescreen.cpp \
    profilescreen.cpp \
    mainwindow.cpp

HEADERS += \
    styles.h \
    user.h \
    userdatabase.h \
    authmanager.h \
    disc.h \
    gamescene.h \
    loginscreen.h \
    signupscreen.h \
    homescreen.h \
    profilescreen.h \
    mainwindow.h
