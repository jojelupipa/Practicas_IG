// EJERCICIO DEFENSA

#include "../include/esfera.h"

Esfera::Esfera(){

    // Crearemos el perfil girando 180 grados el punto (0,1,0) sobre el eje Z, posteriormente generaremos la esfera a partir de ese perfil
const float MUESTRAS = 100;
    _vertex3f punto_generador = _vertex3f(0,1,0);
    for(int i = 0; i <MUESTRAS ; i++){

      perfil_points.push_back(_vertex3f( sin((i*2*M_PI)/MUESTRAS)*punto_generador.y,cos((i*2*M_PI)/MUESTRAS)*punto_generador.y,punto_generador.z ));

    }

    generador();
}

//  sin((i*2*M_PI)/NMUESTRAS)*  )

//  cos((i*2*M_PI)/NMUESTRAS)*
