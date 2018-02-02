//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include <QApplication>
#include <QMenuBar>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QScrollArea>

#include "../include/window.h"
#include "../include/glwidget.h"
#include "../include/tetraedro.h"
#include "../include/cubo.h"

_window::_window()
{
  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QWidget *Central_widget = new QWidget(this);

  QFrame *Framed_widget= new QFrame(Central_widget);
  Framed_widget->setSizePolicy(Q);
  Framed_widget->setFrameStyle(QFrame::Panel);
  Framed_widget->setLineWidth(3);


  GL_widget = new _gl_widget(this);
  GL_widget->setSizePolicy(Q);

  QHBoxLayout *Horizontal_frame = new QHBoxLayout();
  Horizontal_frame->setContentsMargins(1,1,1,1);

  Horizontal_frame->addWidget(GL_widget);
  Framed_widget->setLayout(Horizontal_frame);

  QHBoxLayout *Horizontal_main = new QHBoxLayout(Central_widget);

  Horizontal_main->addWidget(Framed_widget);

  Central_widget->setLayout(Horizontal_main);
  setCentralWidget(Central_widget);

  // actions for file menu
  QAction *Exit = new QAction(QIcon("./icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), this, SLOT(close()));
  /*
  // Actions when key is pushed down (test)

    QAction *DrawPoints = new QAction(this);
    DrawPoints->setShortcut(tr("1"));
    connect(DrawPoints,0, )
    */
  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Exit);
  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

/*
  // Adding Ply Menu
  QMenu *Ply_menu=menuBar()->addMenu((tr("&Ply")));
  Ply_menu->addAction(this->GL_widget->loadAnt());
  Ply_menu->addAction(this->GL_widget->loadBet());
  Ply_menu->addAction(this->GL_widget->loadIco());
  Ply_menu->addAction(this->GL_widget->loadCar());
*/




  setWindowTitle(tr("esqueleto_qt (Jesús Sánchez de Lechina)"));


  resize(800,800);
}


