#ifndef TETRAEDRO_H
#define TETRAEDRO_H

/* Jesús Sánchez de Lechina Tejada
 *
 *
 **/

#include "objeto3d.h"

class Tetraedro : public Objeto3D{

private:
    const double DIST = 0.5;

public:

    Tetraedro(); // Tetraedro predeterminado irregular

    Tetraedro& operator =(Tetraedro&& other);
};
#endif // TETRAEDRO_H
