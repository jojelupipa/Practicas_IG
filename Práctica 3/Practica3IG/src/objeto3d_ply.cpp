#include "../include/objeto3d_ply.h"
Objeto3DPly::Objeto3DPly(string nombre){
    leerFichero(nombre);
}

bool Objeto3DPly::leerFichero(string nombre){
    _file_ply File_ply;
    if (File_ply.open(nombre)){
      File_ply.read(v_points,v_triangulos);
      //std::cout << "Archivo leído correctamente" << std::endl;
      return true;
    }
    else {
        std::cout << "El archivo no se pudo leer" << std::endl;
        return false;
    }
  }

