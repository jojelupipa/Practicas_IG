#include "../include/tubo.h"

Tubo::Tubo(){
    // Definimos el perfil
    perfil_points.resize(2);
    perfil_points.at(0) = _vertex3f(DIST,DIST,0);
    perfil_points.at(1) = _vertex3f(DIST,-DIST,0);

    generador();
}
