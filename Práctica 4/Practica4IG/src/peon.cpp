#include "../include/peon.h"

Peon::Peon(){
    _file_ply File_ply;

    if (File_ply.open("../Practica2IG/data/peon.ply")){
        vector<_vertex3i> unused;
      File_ply.read(perfil_points, unused);
      std::cout << "Peon leído correctamente" << std::endl;
    }
    else
        std::cout << "Error en la lectura del perfil" << std::endl;

    generador();
}
