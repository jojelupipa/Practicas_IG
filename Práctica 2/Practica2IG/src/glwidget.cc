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

   cubo = Cubo();
   tetraedro = Tetraedro();

  objeto_leido = Objeto3DPly(DATA + FILENAME);
  obj_revolucion = Vaso();            // Elegir entre cilindroprefab, vaso, reversevaso, tubo o cono...
  // Defensa: Tubo, Vaso, ReverseVaso
  who_is_visible = 0;
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
  case Qt::Key_3:ActivateLoaded();break;
  case Qt::Key_4:ActivateRevolution();break;
      //Defensa
  case Qt::Key_Q:objeto_leido = Objeto3DPly(DATA + "ant.ply"); break;
  case Qt::Key_W:objeto_leido = Objeto3DPly(DATA + "beethoven.ply"); break;
  case Qt::Key_E:objeto_leido = Objeto3DPly(DATA + "big_dodge.ply"); break;
  case Qt::Key_R:objeto_leido = Objeto3DPly(DATA + "icosahedron_ascii.ply"); break;
  case Qt::Key_5:obj_revolucion=Cono();break;
  case Qt::Key_6:obj_revolucion = CilindroPrefab();break;
      //
  case Qt::Key_P:SelectPointMode();break;
  case Qt::Key_L:SelectLineMode();break;
  case Qt::Key_F:SelectFillMode();break;
  case Qt::Key_C:SelectChessMode();break;

  }

  update();
}


// Implementación de los nuevos métodos

// Métodos que gestionan la visibilidad de las figuras

void _gl_widget::ActivateCube(){
    visibilizador(1);

}

void _gl_widget::ActivateTetrahedron(){
    visibilizador(2);

}

void _gl_widget::ActivateLoaded(){
    visibilizador(3);
}

void _gl_widget::ActivateRevolution(){
    visibilizador(4);
}

// Métodos que controlan los flags de dibujo

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

void _gl_widget::visibilizador(int index){
    // TODO: We might need to add a clear_window() right here
    visibilitySwapper(who_is_visible);

    if(index != who_is_visible){
        visibilitySwapper(index);
        who_is_visible = index;
    }
    else{
        who_is_visible = 0; // Cuando nadie es visible no se hace nada
        clear_window();
    }
}

// Selector de figuras en formato Ply

void _gl_widget::loadAnt(){objeto_leido.leerFichero("../data/ant.ply");}

void _gl_widget::loadCar(){objeto_leido.leerFichero("../data/big_dodge.ply");}

void _gl_widget::loadIco(){objeto_leido.leerFichero("../data/icosahedron_ascii.ply");}

void _gl_widget::loadBet(){objeto_leido.leerFichero("../data/beethoven.ply");}


void _gl_widget::visibilitySwapper(int index){
    switch(index){
    case 1: cubo.SwapVisible(); break;
    case 2:tetraedro.SwapVisible(); break;
    case 3: objeto_leido.SwapVisible(); break;
    case 4: obj_revolucion.SwapVisible(); break;
    default:break;
    }
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
    switch(who_is_visible)
    {
    case 1: DrawManager(cubo); break;
    case 2:DrawManager(tetraedro); break;
    case 3: DrawManager(objeto_leido); break;
    case 4: DrawManager(obj_revolucion); break;
    default:break;
    }
}


void _gl_widget::DrawManager(Objeto3D obj)
{
    if(pointsmode)
        obj.DrawPoints();
    if(linesmode)
        obj.DrawLines();
    if(fillmode)
        obj.DrawTriangles();
    if(chessmode)
        obj.DrawChess();

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

