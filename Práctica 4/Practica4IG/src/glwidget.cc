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

    // Añadiendo el Qtimer
    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(idle()));
    timer->start(30);
    //

    setMinimumSize(300, 300);
    setFocusPolicy(Qt::StrongFocus);

    cubo = Cubo();
    tetraedro = Tetraedro();

    objeto_leido = Objeto3DPly(DATA + FILENAME);
    obj_revolucion = Esfera();//Vaso();            // Elegir entre cilindroprefab, vaso, reversevaso, tubo o cono...
    who_is_visible = 6;

    // Variables P3
    speed = 0;
    angle = 0;
    angle_2 = 0;

    // Variables P4
    light1_angle = 0;
    light2_angle = -1;
    material = 1;

    tablero = Tablero(TABLERO_SIZE);
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
  case Qt::Key_5:ActivateHierarchy();break;
  case Qt::Key_6:ActivateBoard();break;

  case Qt::Key_P:SelectPointMode();break;
  case Qt::Key_L:SelectLineMode();break;
  case Qt::Key_F:SelectFillMode();break;
  case Qt::Key_C:SelectChessMode();break;

  // Teclas aumentar/reducir la velocidad de la animación
  case Qt::Key_N:speed+=1;break;
  case Qt::Key_M:speed-=1;break;
  //P4
      //Visualizar normales
  case Qt::Key_F12:SelectNormalMode();break;
      // Activar/modificar iluminación
            //Seleccionar el modo iluminación
  case Qt::Key_I:SelectLightMode();break;
            //Alternar entre modo plano y suavizado
  case Qt::Key_S:SwapLightMode();break;
            //Aumentar/activar el grado de rotación de la luz puntual 1
  case Qt::Key_F1:light1_angle+=1;break;
            //Aumentar/disminuir la distancia de la luz focal
  case Qt::Key_F8:light1_position+=0.1;break;
  case Qt::Key_F9:light1_position-=0.1;break;
            //Aumentar/activar el grado de rotación de la luz direccional 2
  case Qt::Key_F2:light2_angle+=1;break;
            //Desactivar luces:
  case Qt::Key_F3:light1_angle = -1; light1_position = 0; break;
  case Qt::Key_F4:light2_angle = -1;break;
            //Cambiar el material seleccionado
  case Qt::Key_F5:material = 1; break;
  case Qt::Key_F6:material = 2; break;
  case Qt::Key_F7:material = 3; break;
      //Activar/desactivar textura
  case Qt::Key_T:SelectTextureMode();break;

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

void _gl_widget::ActivateHierarchy(){
    visibilizador(5);
}

void _gl_widget::ActivateBoard(){
    visibilizador(6);
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
    if(lightmode)
        SelectLightMode();

    fillmode? fillmode = false : fillmode = true;

}
void _gl_widget::SelectChessMode(){
    if(fillmode)
        SelectFillMode();
    if(lightmode)
        SelectLightMode();
    chessmode? chessmode = false : chessmode = true;

}
void _gl_widget::SelectNormalMode(){
    normalmode? normalmode = false : normalmode = true;
}

void _gl_widget::SelectLightMode(){
    if(fillmode)
        SelectFillMode();
    if(chessmode)
       SelectChessMode();
    lightmode? lightmode = false : lightmode = true;
}

void _gl_widget::SwapLightMode(){
    flat? flat = false : flat = true;
}

void _gl_widget::SelectTextureMode(){
    texture? texture = false : texture = true;
}

void _gl_widget::visibilizador(int index){
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




void _gl_widget::visibilitySwapper(int index){
    switch(index){
    case 1: cubo.SwapVisible(); break;
    case 2:tetraedro.SwapVisible(); break;
    case 3: objeto_leido.SwapVisible(); break;
    case 4: obj_revolucion.SwapVisible(); break;
    case 5: jerarquico.SwapVisible();break;
    case 6: tablero.SwapVisible();break;
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

      glFrustum((double)(-this->width())/this->height(),(double)(this->width())/this->height(),Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
//      glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE); // <--- Antes estaba esto
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
  glLineWidth(1);
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
    case 5: HierarchyDrawManager(jerarquico); break;
    case 6: DrawManager(tablero);break;
    default:break;
    }
}


void _gl_widget::DrawManager(Objeto3D obj)
{

    if(pointsmode)
        obj.DrawPoints();
    if(linesmode)
        obj.DrawLines();
    if(normalmode)
        obj.DrawNormal();
    if(fillmode)
        obj.DrawTriangles();
    if(chessmode)
        obj.DrawChess();
    if(lightmode)
        flat? obj.DrawLightFlat(material,light1_angle,light2_angle,light1_position) : obj.DrawLightSmooth(material, light1_angle,light2_angle,light1_position);
    if(texture && who_is_visible ==6){
        tablero.DrawTexture(FRAME,POSITION);
    }


}

void _gl_widget::HierarchyDrawManager(SoporteWatt obj) // Cambiar tipo de dato del argumento para mostrar otras partes
{
    obj.RotateBar(angle,angle_2,speed);
    if(pointsmode)
        obj.DrawPoints();
    if(linesmode)
        obj.DrawLines();
    if(fillmode)
        obj.DrawTriangles();
    if(chessmode)
        obj.DrawChess();
}

/* Para dibujar exclusivamente BrazoWatt. Descomentar esto y que DrawManager llame a este método


void _gl_widget::HierarchyDrawManager(BrazoWatt obj)
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

*/

void _gl_widget::idle(){
    angle = (int)(angle + speed)%360;
    bool umbral;
    if (speed >=3){
        umbral = true;
        angle_2 = (int)(angle_2 + speed)%360;
    }
    jerarquico.SetUmbral(umbral);
    paintGL();
    update();
}

// Selector de figuras en formato Ply

void _gl_widget::loadAnt(){objeto_leido.leerFichero("../data/ant.ply");}

void _gl_widget::loadCar(){objeto_leido.leerFichero("../data/big_dodge.ply");}

void _gl_widget::loadIco(){objeto_leido.leerFichero("../data/icosahedron_ascii.ply");}

void _gl_widget::loadBet(){objeto_leido.leerFichero("../data/beethoven.ply");}

//*//////////////////////////////////////////////////////
// P4 Práctica 4
//*//////////////////////////////////////////////////////



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
  update();
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

