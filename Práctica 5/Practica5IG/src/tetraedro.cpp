#include "../include/tetraedro.h"

Tetraedro::Tetraedro(){ // Tetraedro (irregular) predeterminado inscrito en el cubo predeterminado unidad
    v_points.resize(4);
    v_points.at(0) = _vertex3f(DIST,-DIST,DIST);
    v_points.at(1) = _vertex3f(DIST,-DIST,-DIST);
    v_points.at(2) = _vertex3f(-DIST,-DIST,DIST);
    v_points.at(3) = _vertex3f((DIST/3.0),DIST,(DIST/3.0));


    v_triangulos.resize(4);
    v_triangulos.at(0) = _vertex3i(1,0,2);
    v_triangulos.at(1) = _vertex3i(0,1,3);
    v_triangulos.at(2) = _vertex3i(1,2,3);
    v_triangulos.at(3) = _vertex3i(2,0,3);

    visible = false;
    NormalGen();
}

Tetraedro& Tetraedro::operator =(Tetraedro&& other) {
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
    }
    return *this;
}
