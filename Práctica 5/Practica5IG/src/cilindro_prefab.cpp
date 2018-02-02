#include "../include/cilindro_prefab.h"

CilindroPrefab::CilindroPrefab(){

    // Definimos el perfil
    perfil_points.resize(4);
    perfil_points.at(0) = _vertex3f(DIST,DIST,0);
    perfil_points.at(1) = _vertex3f(DIST,-DIST,0);
    perfil_points.at(2) = _vertex3f(0,DIST,0);
    perfil_points.at(3) = _vertex3f(0,-DIST,0);

    generador();
/*
    // Definimos los puntos
    for(int i = 0; i < NMUESTRAS; ++i){
        v_points.push_back(_vertex3f(DIST*cos((i*2*M_PI)/NMUESTRAS),DIST,DIST*sin((i*2*M_PI)/NMUESTRAS)));
        v_points.push_back(_vertex3f(DIST*cos((i*2*M_PI)/NMUESTRAS),-DIST,DIST*sin((i*2*M_PI)/NMUESTRAS)));
    }
    v_points.push_back(perfil_points.at(2)); // at (size -2) Tapa superior
    v_points.push_back(perfil_points.at(3)); // at (size -1) Tapa inferior
*/

    // Definimos los triángulos

//    int v_size = v_points.size();                       // Estas dos variables son usadas
//    int n_puntos_sin_tapas = n_puntos_perfil - n_tapas; // con fines de eficiencia
/*
    v_triangulos.push_back(_vertex3i(n_puntos_sin_tapas,0,v_size - 2));
    v_triangulos.push_back(_vertex3i(n_puntos_sin_tapas,i+1,i+n_puntos_sin_tapas));
    v_triangulos.push_back(_vertex3i(i,i+n_puntos_sin_tapas,i+n_puntos_sin_tapas -1));
    v_triangulos.push_back(_vertex3i(i,i+n_puntos_sin_tapas,v_size - 1));
    */

/*
    for(int i = 0; i < v_size-2;++i){
        if(i%n_puntos_sin_tapas == 0){
            v_triangulos.push_back(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),v_size - 2));
            v_triangulos.push_back(_vertex3i(i,i+1,(i+n_puntos_sin_tapas)%(v_size-2)));
        }
        else{
            v_triangulos.push_back(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),(i+n_puntos_sin_tapas -1)%(v_size-2)));
            v_triangulos.push_back(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),v_size - 1));
        }

    }
*/


    /* Estructura general que deben seguir estos bucles de inicialización de los triángulos:
     * for(int i = 0; o < v_size - 2; i++){ // Es decir, el número de puntos exceptuando las tapas
     *      switch(i%n_puntos_sin_tapas){   // Calculamos si estamos en un vértice que se une con alguna tapa
     *          case 0:
     *              v_triangulos.add(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),v_size - 2)); // En el caso de haber tapa superior
     *              v_triangulos.add(_vertex3i(i,i+1,(i+n_puntos_sin_tapas)%(v_size-2)));
     *              break;
     *          case n_puntos_sin_tapas-1: // Esto tiene que hacerse con if/else, pues este numero tiene que ser conocido en compilación
     *              v_triangulos.add(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),(i+n_puntos_sin_tapas -1)%(v_size-2)));
     *              v_triangulos.add(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),v_size - 1)); // En el caso de haber tapa inferior
     *              break;
     *          default:
     *              v_triangulos.add(_vertex3i(i,i+1,(i+n_puntos_sin_tapas)%(v_size-2)));
     *              v_triangulos.add(_vertex3i(i,(i+n_puntos_sin_tapas)%(v_size-2),(i+n_puntos_sin_tapas -1)%(v_size-2)));
     */
}

CilindroPrefab& CilindroPrefab::operator =(CilindroPrefab&& other) {
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
        this->perfil_points= other.perfil_points;
    }
    return *this;
}

CilindroPrefab& CilindroPrefab::operator =(const CilindroPrefab& other){
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
        this->perfil_points = other.perfil_points;
    }
    return *this;
}
