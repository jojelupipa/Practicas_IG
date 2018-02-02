#ifndef OBJETO3D_PLY_H
#define OBJETO3D_PLY_H

#include "objeto3d.h"

class Objeto3DPly:public Objeto3D{

public:

    Objeto3DPly(){}
    /**
     * @brief Constructor dado el nombre del archivo de un Objeto3DPly
     * @param nombre Nombre del archivo a abrir
     */
    Objeto3DPly(std::string nombre);

    /**
     * @brief Lee del fichero en formato ply y lo inserta en un objeto 3d
     * @param nombre: Nombre del archivo a leer
     * @return Si la lectura fue correcta o no
     */
    bool leerFichero(std::string nombre);
};
#endif // OBJETO3D_PLY_H
