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

// P5: Interacción y cámaras
#include "camara.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <GL/glu.h>


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
    const std::string DATA = "../Practica5IG/data/";
    const string FILENAME = "beethoven.ply"; // Cambiar para cambiar el fichero a leer (ant.ply,icosahedron_ascii.ply,
                                                     // big_dodge.ply, beethoven.ply)

    //P4 Tamaño tablero:
    int TABLERO_SIZE = 4;
    _vertex4f FRAME ={0,0,1,1};   // Se pintará la imagen que hay entre el "(F_0,F_1) y el (F_2,F_3)"
    _vertex4f POSITION ={1,1,2,2};    // Todos estos valores deben ser menores estrictos que el tamaño del tablero

    /** Valores notables:
     * Toda la imagen en todo el tablero: FRAME ={0,0,1,1} y POSITION ={0,0,TABLERO_SIZE,TABLERO_SIZE}
     * Toda la imagen en parte del tablero: FRAME ={0,0,1,1} y POSITION ={0<=x,0<=y,z<=SIZE,t<=SIZE}
     * Parte de la imagen en parte del tablero: FRAME ={0<=a,0<=b,c<=1,d<=1} y POSITION ={0<=x,0<=y,z<=SIZE,t<=SIZE}
     */

    // P5 Mouse y cámara


    Camara v_camara[2]; // Cámara 0: Cámara de mundo, estándar. Cámara 1: Cámara de objeto seleccionado.
    int selected_camera;
    int last_camera_used;
    void updateCamera();

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    int last_x, last_y;

    void pick(int x, int y);

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
  void SelectFlatLightMode();
  void SelectSmoothLightMode();
  void SwapLightMode();

  // Modificadores de luz y materiales
  void ChangeLight1Distance(int distance);
  void ChangeLight1Angle(int angle);

  void ChangeLight1xAngle(int angle);
  void ChangeLight2yAngle(int angle);
  void ChangeLight2Angle(int angle);
  void switchLight1();
  void switchLight2();

  void selectMaterial(int mat);
  void selectFirstMaterial(){selectMaterial(1);}
  void selectSecondMaterial(){selectMaterial(2);}
  void selectThirdMaterial(){selectMaterial(3);}

  // Modificadores tablero
  void sizeChange(int orden);
  /**
   * @brief modifyFrame: Modifica el frame de la textura que se dibujará en el tablero
   * @param x1: Coordenada x del primer punto del rectángulo
   * @param y1: Coordenada y del primer punto del rectángulo
   * @param x2: Coordenada x del segundo punto del rectángulo
   * @param y2: Coordenada y del segundo punto del rectángulo
   */
  void modifyFrame(double x1, double y1, double x2, double y2);

  /**
   * @brief modifyPosition: Modifica los cuadrantes en los que se dibujará la textura
   * @param x1
   * @param y1
   * @param x2
   * @param y2
   */
  void modifyPosition(int x1, int y1, int x2, int y2);

  // Modificadores cámara
  /**
   * @brief increaseZoom: Incrementa o decrementa el zoom de la camera estándar
   * @param increase: Indica si ha de aumentarse o decrementarse
   */
  void increaseZoom(bool increase);

  /**
   * @brief selectHorizontalCameraRotation: Rota la cámara horizontalmente, respecto al eje Y
   * @param angulo
   */
  void selectHorizontalCameraRotation(int angulo);

  /**
   * @brief selectVerticalCameraRotation: Rota la cámara verticalmente, respecto al eje X
   * @param angulo
   */
  void selectVerticalCameraRotation(int angulo);

  /**
   * @brief switchProjection: Cambia entre proyección paralela y perspectiva.
   */
  void switchProjection();

  /**
   * @brief switchSelectedCamera: Cambia entre las dos cámaras existentes
   */
  void switchSelectedCamera();

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;




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

  /**
   * @brief visibilizador:  Maneja la visualización de las figuras. Activa/desactiva el objeto actual. En caso de ser distinto activa
   *                        el indicado y actualiza la variable who_is_visible
   * @param index: Índice: 1: Cubo 2: Tetraedro 3: Figura PLY 4: Figura Revolución 5: Objeto Jerárquico 6: Tablero
   */
  void visibilizador(int index);

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

  double light1_angle; // Ángulo de la luz 1 sobre y
  double light1x_angle; // sobre eje x
  double light1_position;
  double light2_angle; // angulo de la luz 2 sobre x
  double light2y_angle; //sobre eje y
  int material; // Material seleccionado

  /**
   * @brief who_is_visible: Variable que indica qué objeto es visible, para simplificar las tareas de activación.
   *                        1: Cubo 2: Tetraedro 3:Figura PLY 4: Figura Revolución 5: Objeto Jerárquico 6: Tablero
   */
  int who_is_visible;



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
  bool lightmode = true;
  bool flat = false;
  bool texture = false;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance_x;
  float Observer_distance_y;
  float Observer_distance_z;

  /**
   * @brief perspective_projection: True si la proyección de la cámara debe ser paralela o de perspectiva.
   */
  bool perspective_projection = true;

public slots:
  /**
 * @brief idle: Método que se ejecutará cada vez que el timer llegue a cero para comprobar la animación.
 */
void idle();
};

#endif
