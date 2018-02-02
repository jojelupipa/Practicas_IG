#ifndef TRIANGULO_H
#define TRIANGULO_H
/* Jesús Sánchez de Lechina Tejada
 *
 * Permite generar triángulos
 *
 **/

#include <vector>
#include "punto.h"

class Triangulo : public Punto{

protected:
    std::vector<_vertex3i> v_triangulos;    // _vertex3i porque guardamos los tres enteros que corresponden a las posiciones que
                                            // ocupan los vértices conforman cada triángulo


public:

    void DrawLines();

    void DrawTriangles();

    void DrawChess();

};

#endif // TRIANGULO_H
