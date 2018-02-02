#ifndef CUBO_H
#define CUBO_H


/* Jesús Sánchez de Lechina Tejada
 *
 * Permite generar cubos
 *
 **/

#include "triangulo.h"

class Cubo : public Triangulo{
private:
    bool visible;

    const double DIST = 0.5;
public:

    Cubo(){                                 // Cubo predeterminado
        v_points.push_back(_vertex3f(DIST,-DIST,DIST));
        v_points.push_back(_vertex3f(DIST,DIST,DIST));
        v_points.push_back(_vertex3f(-DIST,DIST,DIST));
        v_points.push_back(_vertex3f(-DIST,-DIST,DIST));

        v_points.push_back(_vertex3f(DIST,-DIST,-DIST));
        v_points.push_back(_vertex3f(DIST,DIST,-DIST));
        v_points.push_back(_vertex3f(-DIST,DIST,-DIST));
        v_points.push_back(_vertex3f(-DIST,-DIST,-DIST));

        // Modelamos todos los triángulos del cubo
        v_triangulos.push_back(_vertex3i(0,2,3)); //FrontX
        v_triangulos.push_back(_vertex3i(0,1,2));

        v_triangulos.push_back(_vertex3i(7,5,4)); //BackX
        v_triangulos.push_back(_vertex3i(6,5,7));

        v_triangulos.push_back(_vertex3i(3,6,7)); //FrontZ
        v_triangulos.push_back(_vertex3i(3,2,6));

        v_triangulos.push_back(_vertex3i(0,4,1)); //BackZ
        v_triangulos.push_back(_vertex3i(4,5,1));

        v_triangulos.push_back(_vertex3i(2,1,6)); //TopY
        v_triangulos.push_back(_vertex3i(1,5,6));

        v_triangulos.push_back(_vertex3i(3,7,4)); //BottomY
        v_triangulos.push_back(_vertex3i(0,3,4));

        visible = false;
    }

    void SwapVisible(){visible ? visible=false:visible = true;}
    bool IsVisible(){return visible;}
};
#endif // CUBO_H
