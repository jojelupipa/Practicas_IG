// EJERCICIO DEFENSA

#include "../include/esfera.h"

Esfera::Esfera(){

    // Crearemos el perfil girando 180 grados el punto (0,1,0) sobre el eje Z, posteriormente generaremos la esfera a partir de ese perfil
const float MUESTRAS = 40;
    _vertex3f punto_generador = _vertex3f(0,1,0);
    for(int i = 0; i <MUESTRAS ; i++){

      perfil_points.push_back(_vertex3f( sin((i*2*M_PI)/MUESTRAS)*punto_generador.y,cos((i*2*M_PI)/MUESTRAS)*punto_generador.y,punto_generador.z ));

    }

    compruebaTapas();
    inicializaPuntos();
    inicializaTriangulos();
    NormalGen();
}

void Esfera::NormalGen(){

    float x,y,z;
    for(unsigned int i = 0; i < v_triangulos.size(); i++){
        x = (v_points.at(v_triangulos.at(i)._2).x + v_points.at(v_triangulos.at(i)._1).x + v_points.at(v_triangulos.at(i)._0).x)/3.0;
        y = (v_points.at(v_triangulos.at(i)._2).y + v_points.at(v_triangulos.at(i)._1).y + v_points.at(v_triangulos.at(i)._0).y)/3.0;
        z = (v_points.at(v_triangulos.at(i)._2).z + v_points.at(v_triangulos.at(i)._1).z + v_points.at(v_triangulos.at(i)._0).z)/3.0;
        normales_caras.push_back(_vertex3f(x,y,z));
    }

    NormalVertexGen();
}

//  sin((i*2*M_PI)/NMUESTRAS)*  )

//  cos((i*2*M_PI)/NMUESTRAS)*
