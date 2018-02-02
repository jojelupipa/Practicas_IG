#include "../include/cono.h"

Cono::Cono(){
    // Definimos el perfil
    perfil_points.resize(3);
    perfil_points.at(0) = _vertex3f(DIST,-DIST,0);
    perfil_points.at(1) = _vertex3f(0,DIST,0);
    perfil_points.at(2) = _vertex3f(0,-DIST,0);

    compruebaTapas();
    inicializaPuntos();
    this->inicializaTriangulos();
}

void Cono::inicializaTriangulos(){
    for(unsigned int i = 0; i < v_points.size()-2;++i){
        v_triangulos.push_back(_vertex3i(i,(i+1)%(v_points.size()-2), v_points.size()-2));
        v_triangulos.push_back(_vertex3i(i,(i+1)%(v_points.size()-2), v_points.size()-1));
        }
}
