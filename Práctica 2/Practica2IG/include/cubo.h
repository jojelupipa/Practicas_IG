#ifndef CUBO_H
#define CUBO_H


/* Jesús Sánchez de Lechina Tejada
 *
 * Permite generar cubos
 *
 **/

#include "objeto3d.h"

class Cubo : public Objeto3D{
private:

    const double DIST = 0.5;
public:

    Cubo(); // Cubo predeterminado unidad centrado

    Cubo& operator =(Cubo&& other);
};
#endif // CUBO_H
