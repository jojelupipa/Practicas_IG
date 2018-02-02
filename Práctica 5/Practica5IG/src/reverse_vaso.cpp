#include "../include/reverse_vaso.h"

ReverseVaso::ReverseVaso(){
    // Definimos el perfil
    perfil_points.resize(3);
    perfil_points.at(0) = _vertex3f(DIST/2.0,DIST,0);
    perfil_points.at(1) = _vertex3f(DIST,-DIST,0);
    perfil_points.at(2) = _vertex3f(0,DIST,0);

    generador();
}
