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
#include "reverse_vaso.h"
#include "cono.h"
#include "peon.h"
#include "esfera.h"

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
    const std::string DATA = "../Practica2IG/data/";
    const string FILENAME = "icosahedron_ascii.ply"; // Cambiar para cambiar el fichero a leer (ant.ply,icosahedron_ascii.ply,
                                                     // big_dodge.ply, beethoven.ply)

    /**
     * @brief N_FIGURAS: Número de figuras a usar. Adaptar el valor al número de figuras a usar
     */
    const int N_FIGURAS = 4;
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
  void ActivateLoaded();        // (este es el otro)
  void ActivateRevolution(); //TODO: Implementar estos dos métodos y arreglar el hacerlos visible de forma "cómoda"/legible
  void SelectPointMode();
  void SelectLineMode();
  void SelectFillMode();
  void SelectChessMode();


  /**
   * @brief DrawManager: Se encarga de abstraer el dibujado del objeto visible
   * @param obj: Objeto a dibujar
   */
  void DrawManager(Objeto3D obj);


private:
  _window *Window;

  Cubo cubo;
  Tetraedro tetraedro;
  Objeto3DPly objeto_leido;
  Objeto3DRev obj_revolucion;


  /**
   * @brief who_is_visible: Variable que indica qué objeto es visible, para simplificar las tareas de activación.
   *                        1: Cubo 2: Tetraedro 3:Figura PLY 4: Figura Revolución
   */
  int who_is_visible;

  /**
   * @brief visibilizador:  Maneja la visualización de las figuras. Activa/desactiva el objeto actual. En caso de ser distinto activa
   *                        el indicado y actualiza la variable who_is_visible
   * @param index: Índice: 1: Cubo 2: Tetraedro 3: Figura PLY 4: Figura Revolución
   */
  void visibilizador(int index);

  /**
   * @brief visibilitySwapper: Cambia la visibilidad del objeto indicado
   * @param index: Índice: 1: Cubo 2: Tetraedro 3: Figura PLY 4: Figura Revolución
   */
  void visibilitySwapper(int index);

  bool pointsmode = true;
  bool linesmode = false;
  bool fillmode = false;
  bool chessmode = false;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;
};

#endif
