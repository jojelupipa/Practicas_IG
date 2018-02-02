HEADERS += \
    include/glwidget.h \
    include/window.h \
    include/vertex.h \
    include/punto.h \
    include/triangulo.h \
    include/cubo.h \
    include/tetraedro.h

SOURCES += \
    src/main.cc \
    src/glwidget.cc \
    src/window.cc \
    src/punto.cpp \
    src/triangulo.cpp \
    src/cubo.cpp \
    src/tetraedro.cpp

INCLUDEPATH += /casa/dmartin/codigo/funciontecas/glew/include

LIBS += -L/usr/X11R6/lib64 -lGL \
        -L/casa/dmartin/codigo/funciontecas/glew/lib -lGLEW

CONFIG += c++11
QT += widgets


