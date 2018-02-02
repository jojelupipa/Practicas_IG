//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "../include/window.h"
#include"../include/cubo.h"
int main( int argc, char ** argv ){
    // Esqueleto main
  QApplication Application( argc, argv );
  QSurfaceFormat Format;
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(Format);
  _window Window;
  Window.show();
  return Application.exec();
}
