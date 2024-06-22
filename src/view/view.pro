QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../GifLib/gifImage/qgifimage.cpp \
    ../GifLib/gifLib/dgif_lib.c \
    ../GifLib/gifLib/egif_lib.c \
    ../GifLib/gifLib/gif_err.c \
    ../GifLib/gifLib/gif_font.c \
    ../GifLib/gifLib/gif_hash.c \
    ../GifLib/gifLib/gifalloc.c \
    ../GifLib/gifLib/quantize.c \
    colorpalette.cc \
    scene.cc \
    view.cc \
    main.cc \
    ../controller/controller.cc \
    ../singleton/singleton.cc



HEADERS += \
    ../GifLib/gifImage/qgifglobal.h \
    ../GifLib/gifImage/qgifimage.h \
    ../GifLib/gifImage/qgifimage_p.h \
    ../GifLib/gifLib/gif_hash.h \
    ../GifLib/gifLib/gif_lib.h \
    ../GifLib/gifLib/gif_lib_private.h \
    colorpalette.h \
    scene.h \
    view.h \
    ../controller/controller.h \
    ../singleton/singleton.h


FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
