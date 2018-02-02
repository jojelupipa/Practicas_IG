HEADERS += \
    include/glwidget.h \
    include/window.h \
    include/vertex.h \
    include/cubo.h \
    include/tetraedro.h \
    include/vertices.h \
    include/triangulos.h \
    include/objeto3d.h \
    include/file_ply_stl.h \
    include/objeto3d_ply.h \
    include/objeto3d_rev.h \
    include/cilindro_prefab.h \
    include/vaso.h \
    include/tubo.h \
    include/reverse_vaso.h \
    include/cono.h \
    include/peon.h \
    include/esfera.h \
    include/sphere.h \
    include/brazo_watt.h \
    include/elevador.h \
    include/cabezalwatt.h \
    include/soporte_watt.h \
    include/conector_elevador_watt.h \
    include/tablero.h

SOURCES += \
    src/main.cc \
    src/glwidget.cc \
    src/window.cc \
    src/cubo.cpp \
    src/tetraedro.cpp \
    src/vertices.cpp \
    src/triangulos.cpp \
    src/objeto3d.cpp \
    src/file_ply_stl.cpp \
    src/objeto3d_ply.cpp \
    src/objeto3d_rev.cpp \
    src/cilindro_prefab.cpp \
    src/vaso.cpp \
    src/tubo.cpp \
    src/reverse_vaso.cpp \
    src/cono.cpp \
    src/peon.cpp \
    src/esfera.cpp \
    src/sphere.cpp \
    src/brazo_watt.cpp \
    src/elevador.cpp \
    src/cabezalwatt.cpp \
    src/soporte_watt.cpp \
    src/conector_elevador_watt.cpp \
    src/tablero.cpp

INCLUDEPATH += /casa/dmartin/codigo/funciontecas/glew/include

LIBS += -L/usr/X11R6/lib64 -lGL \
        -L/casa/dmartin/codigo/funciontecas/glew/lib -lGLEW

CONFIG += c++11
QT += widgets


