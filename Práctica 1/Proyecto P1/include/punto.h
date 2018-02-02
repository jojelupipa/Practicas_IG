#ifndef PUNTO_H
#define PUNTO_H

/* Jesús Sánchez de Lechina Tejada
 *
 * Permite generar puntos
 *
 **/


#include <vector>
#include "../include/vertex.h"
#include <GL/glu.h>

class Punto {

protected:

std::vector<_vertex3f> v_points;

public:

void DrawPoints();
};
#endif // PUNTO_H
