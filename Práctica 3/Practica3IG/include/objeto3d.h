#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "triangulos.h"
#include "file_ply_stl.h"

class Objeto3D:public Triangulos{

protected:
    bool visible;

public:

    /**
     * @brief SwapVisible: Activa/desactiva la visibilidad del objeto3D
     */
    void SwapVisible(){visible ? visible=false:visible = true;}

    /**
     * @brief IsVisible: Devuelve si el objeto es actualmente visible
     * @return visibilidad
     */
    bool IsVisible(){return visible;}


};


#endif // OBJETO3D_H
