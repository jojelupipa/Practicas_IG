#include "../include/cubo.h"

Cubo::Cubo()
        {                                 // Cubo predeterminado
            v_points.resize(8);
            v_points.at(0) =_vertex3f(DIST,-DIST,DIST);
            v_points.at(1) =_vertex3f(DIST,DIST,DIST);
            v_points.at(2) =_vertex3f(-DIST,DIST,DIST);
            v_points.at(3) =_vertex3f(-DIST,-DIST,DIST);

            v_points.at(4) =_vertex3f(DIST,-DIST,-DIST);
            v_points.at(5) =_vertex3f(DIST,DIST,-DIST);
            v_points.at(6) =_vertex3f(-DIST,DIST,-DIST);
            v_points.at(7) =_vertex3f(-DIST,-DIST,-DIST);

            // Modelamos todos los triángulos del cubo
            v_triangulos.resize(12);
            v_triangulos.at(0)= _vertex3i(0,2,3); //FrontX
            v_triangulos.at(1)= _vertex3i(0,1,2);

            v_triangulos.at(2)= _vertex3i(7,5,4); //BackX
            v_triangulos.at(3)= _vertex3i(6,5,7);

            v_triangulos.at(4)= _vertex3i(3,6,7); //FrontZ
            v_triangulos.at(5)= _vertex3i(3,2,6);

            v_triangulos.at(6)= _vertex3i(0,4,1); //BackZ
            v_triangulos.at(7)= _vertex3i(4,5,1);

            v_triangulos.at(8)= _vertex3i(2,1,6); //TopY
            v_triangulos.at(9)= _vertex3i(1,5,6);

            v_triangulos.at(10)= _vertex3i(3,7,4); //BottomY
            v_triangulos.at(11)= _vertex3i(0,3,4);

            visible = false;
        }

Cubo& Cubo::operator =(Cubo&& other) {
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
    }
    return *this;
}


