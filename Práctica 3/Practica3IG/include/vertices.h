#ifndef VERTICES_H
#define VERTICES_H

/* Jesús Sánchez de Lechina Tejada
 *
 * Permite generar puntos
 *
 **/


#include <vector>
#include "../include/vertex.h"
#include <GL/glu.h>

class Vertices {

protected:

std::vector<_vertex3f> v_points;

public:

void DrawPoints();
};
#endif // VERTICES_H
