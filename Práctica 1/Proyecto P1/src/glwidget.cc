//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include "../include/glwidget.h"
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <math.h>

#include "../include/window.h"

using namespace std;
using namespace _gl_widget_ne;

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;

  case Qt::Key_1:ActivateCube();break;
  case Qt::Key_2:ActivateTetrahedron();break;
  case Qt::Key_P:SelectPointMode();break;
  case Qt::Key_L:SelectLineMode();break;
  case Qt::Key_F:SelectFillMode();break;
  case Qt::Key_C:SelectChessMode();break;

  }

  update();
}


// Implementación de los nuevos métodos
void _gl_widget::ActivateCube(){
    if(!cubo.IsVisible()){
        cubo.SwapVisible();
        if(tetraedro.IsVisible())
            tetraedro.SwapVisible(); // Oculta el tetraedro cuando este aparece
    }
    else{
        cubo.SwapVisible();
        clear_window();
    }
}

void _gl_widget::ActivateTetrahedron(){
    if(!tetraedro.IsVisible()){
        tetraedro.SwapVisible();
        if(cubo.IsVisible())
            cubo.SwapVisible();// Oculta el cubo cuando este aparece
    }
    else{
        tetraedro.SwapVisible();
        clear_window();
    }
}
void _gl_widget::SelectPointMode(){
       pointsmode ? pointsmode = false : pointsmode = true;
}
void _gl_widget::SelectLineMode(){
    linesmode ? linesmode = false : linesmode = true;
}
void _gl_widget::SelectFillMode(){
    if(chessmode)
       SelectChessMode();
    fillmode? fillmode = false : fillmode = true;

}
void _gl_widget::SelectChessMode(){
    if(fillmode)
        SelectFillMode();
    chessmode? chessmode = false : chessmode = true;

}


//**************************************************************************
//
//***************************************************************************

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void _gl_widget::draw_axis()
{
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void _gl_widget::draw_objects()
{
    if(cubo.IsVisible()){

        if(pointsmode)
            cubo.DrawPoints();
        if(linesmode)
            cubo.DrawLines();
        if(fillmode)
            cubo.DrawTriangles();

        if(chessmode)
            cubo.DrawChess();
        }


    if(tetraedro.IsVisible()){
        if(pointsmode)
            tetraedro.DrawPoints();
        if(linesmode)
            tetraedro.DrawLines();
        if(fillmode)
            tetraedro.DrawTriangles();

        if(chessmode)
            tetraedro.DrawChess();
        }
    }






//*************************************************************************
//
//*************************************************************************

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_axis();
  draw_objects();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


//*************************************************************************
//
//*************************************************************************

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
    }

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;
}

