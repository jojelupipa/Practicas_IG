#ifndef TETRAEDRO_H
#define TETRAEDRO_H

/* Jesús Sánchez de Lechina Tejada
 *
 *
 **/

#include "triangulo.h"

class Tetraedro : public Triangulo{

private:
    bool visible;
    const double DIST = 0.5;

public:

    Tetraedro(){ // Tetraedro (irregular) predeterminado inscrito en el cubo predeterminado unidad
        v_points.push_back(_vertex3f(DIST,-DIST,DIST));
        v_points.push_back(_vertex3f(DIST,-DIST,-DIST));
        v_points.push_back(_vertex3f(-DIST,-DIST,DIST));
        v_points.push_back(_vertex3f((DIST/2.0),DIST,(DIST/2.0)));


        v_triangulos.push_back(_vertex3i(0,1,2));
        v_triangulos.push_back(_vertex3i(0,1,3));
        v_triangulos.push_back(_vertex3i(1,2,3));
        v_triangulos.push_back(_vertex3i(0,2,3));

        visible = false;
    }

    void SwapVisible(){visible ? visible=false:visible = true;}
    bool IsVisible(){return visible;}

};
#endif // TETRAEDRO_H
