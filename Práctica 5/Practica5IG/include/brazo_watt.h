#ifndef BRAZO_WATT_H
#define BRAZO_WATT_H
#include "conector_elevador_watt.h"
#include "cilindro_prefab.h"
#include "sphere.h"
#include <cmath>

class BrazoWatt{
private:
    Objeto3DRev esfera;
    CilindroPrefab cilindro;
    ConectorElevadorWatt conector;

    double angle;     // Ángulo de apertura de los brazos
    double offset_esfera;  // Desplazamiento vertical de la esfera al abrirse (para simular su anclaje)
    double offset_cilindro;  // Idem, cilindro
    double offset_conector;

    /**
     * @brief Transformaciones: Gestiona en qué modo se va a pintar. Lo usamos para no tener que realizar las mismas transformaciones para cada
     *                          modo en el que queramos pintar
     * @param modo: 1: Puntos 2: Aristas 3: Relleno Simple 4: Relleno Ajedrez
     */
    void Transformaciones(int modo);
public:
    BrazoWatt();

    /**
     * @brief BrazoWatt: Lo necesitamos para poder realizar la gestión de dibujado de esta figura
     * @param brazo
     */
    BrazoWatt(const BrazoWatt& brazo);
    void SwapVisible();
    void DrawPoints();
    void DrawLines();
    void DrawTriangles();
    void DrawChess();

    void SpeedChanges(double speed);
};

#endif // BRAZO_WATT_H
