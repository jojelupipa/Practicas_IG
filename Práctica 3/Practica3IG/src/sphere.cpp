#include "../include/sphere.h"


Sphere::Sphere(){
    leerFichero("../Practica3IG/data/sphere.ply");
    for(unsigned int i = 0; i < v_points.size(); i++){
        v_points.at(i).x /= 127.0;
        v_points.at(i).y /= 127.0;
        v_points.at(i).z /= 127.0;
    }
}
