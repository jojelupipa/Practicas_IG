#ifndef GLWIDGET_H
#define GLWIDGET_H
//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "vertex.h"

// Own includes
#include "objeto3d_ply.h"
#include "objeto3d_rev.h"
#include "cubo.h"
#include "tetraedro.h"
#include "cilindro_prefab.h"
#include "vaso.h"
#include "tubo.h"
#include "esfera.h"
#include "reverse_vaso.h"
#include "cono.h"
//#include "peon.h"
#include "sphere.h"

// P3: Jerarquía
//#include "brazo_watt.h"
//#include "elevador.h"
//#include "cabezalwatt.h"
#include "soporte_watt.h"
#include <QTimer> // Da soporte a la animación del movimiento
#include <QDebug>

// P4: Iluminación y texturas
#include "tablero.h"


namespace _gl_widget_ne {

  const _vertex3f COLORS[]={{0,0,0},{1,0,0},{0,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,0},{1,1,1}};

  const float X_MIN=-1;
  const float X_MAX=1;
  const float Y_MIN=-1;
  const float Y_MAX=1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=10;

  const float ANGLE_STEP=1;

  // axis
  const int AXIS_SIZE=5000;
}


class _window;

class _gl_widget : public QOpenGLWidget
{
    Q_OBJECT

private:
    const std::string DATA = "../Practica4IG/data/";
    const string FILENAME = "beethoven.ply"; // Cambiar para cambiar el fichero a leer (ant.ply,icosahedron_ascii.ply,
                                                     // big_dodge.ply, beethoven.ply)

    //P4 Tamaño tablero:
    const int TABLERO_SIZE = 4;
    const _vertex4f FRAME ={0.5,0.5,1,1};   // Se pintará la imagen que hay entre el "(F_0,F_1) y el (F_2,F_3)"
    const _vertex4f POSITION ={1,1,4,2};    // Todos estos valores deben ser menores estrictos que el tamaño del tablero

    /** Valores notables:
     * Toda la imagen en todo el tablero: FRAME ={0,0,1,1} y POSITION ={0,0,TABLERO_SIZE,TABLERO_SIZE}
     * Toda la imagen en parte del tablero: FRAME ={0,0,1,1} y POSITION ={0<=x,0<=y,z<=SIZE,t<=SIZE}
     * Parte de la imagen en parte del tablero: FRAME ={0<=a,0<=b,c<=1,d<=1} y POSITION ={0<=x,0<=y,z<=SIZE,t<=SIZE}
     */


    /**
     * @brief N_FIGURAS: Número de figuras a usar. Adaptar el valor al número de figuras a usar
     */
    const int N_FIGURAS = 5;
public:
    /**
   * @brief Constructor del widget
   * @param Window1 Ventana sobre la que se dibujará
   */
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();


  // Métodos para seleccionar la figura a leer
  void loadAnt();
  void loadCar();
  void loadBet();
  void loadIco();


protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

  //Metodos para seleccionar el objeto a dibujar y el modo de dibujo

  void ActivateCube();
  void ActivateTetrahedron();
  void ActivateLoaded();
  void ActivateRevolution();
  void ActivateHierarchy();
  void ActivateBoard();
  void SelectPointMode();
  void SelectLineMode();
  void SelectFillMode();
  void SelectChessMode();
  void SelectNormalMode();
  void SelectLightMode();
  void SelectTextureMode();
  void SwapLightMode();


  /**
   * @brief DrawManager: Se encarga de abstraer el dibujado del objeto visible
   * @param obj: Objeto a dibujar
   */
  void DrawManager(Objeto3D obj);

  /**
   * @brief HierarchyDrawManager: Abstrae el dibujado del objeto jerárquico
   * @param obj
   */
  void HierarchyDrawManager(SoporteWatt obj); // Cambiar la clase del argumento para mostrar otras partes


private:
  _window *Window;

  Cubo cubo;
  Tetraedro tetraedro;
  Objeto3DPly objeto_leido;
  Objeto3DRev obj_revolucion;
  SoporteWatt jerarquico; //Cambiar la clase del objeto/crear nuevos objetos de otras clases para mostrar las partes en las que se compone
  Tablero tablero;

  double speed; // Velocidad para las animaciones
  double angle; // Ángulo que genera tal velocidad
  double angle_2;

  double light1_angle; // Ángulo de la luz
  double light1_position;
  double light2_angle;
  int material; // Material seleccionado

  /**
   * @brief who_is_visible: Variable que indica qué objeto es visible, para simplificar las tareas de activación.
   *                        1: Cubo 2: Tetraedro 3:Figura PLY 4: Figura Revolución 5: Objeto Jerárquico 6: Tablero
   */
  int who_is_visible;

  /**
   * @brief visibilizador:  Maneja la visualización de las figuras. Activa/desactiva el objeto actual. En caso de ser distinto activa
   *                        el indicado y actualiza la variable who_is_visible
   * @param index: Índice: 1: Cubo 2: Tetraedro 3: Figura PLY 4: Figura Revolución 5: Objeto Jerárquico 6: Tablero
   */
  void visibilizador(int index);

  /**
   * @brief visibilitySwapper: Cambia la visibilidad del objeto indicado
   * @param index: Índice: 1: Cubo 2: Tetraedro 3: Figura PLY 4: Figura Revolución 5: Objeto Jerárquico 6: Tablero
   */
  void visibilitySwapper(int index);

  bool pointsmode = false;
  bool linesmode = false;
  bool fillmode = false;
  bool chessmode = false;
  bool normalmode = false;
  bool lightmode = false;
  bool flat = false;
  bool texture = true;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;


public slots:
  /**
 * @brief idle: Método que se ejecutará cada vez que el timer llegue a cero para comprobar la animación.
 */
void idle();
};

#endif
