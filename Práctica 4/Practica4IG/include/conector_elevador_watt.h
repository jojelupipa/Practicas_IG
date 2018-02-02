#ifndef CONECTOR_ELEVADOR_WATT_H
#define CONECTOR_ELEVADOR_WATT_H
#include "cilindro_prefab.h"

class ConectorElevadorWatt{
private:
    CilindroPrefab cilindro;

    void Transformaciones(int modo);
    double offset;
    double angle;

public:
    ConectorElevadorWatt();

    /**
     * @brief ConectorElevadorWatt: Lo necesitamos para poder realizar la gestión de dibujado de esta figura
     * @param c
     */
    ConectorElevadorWatt(const ConectorElevadorWatt& c);
    void SwapVisible();
    void DrawPoints();
    void DrawLines();
    void DrawTriangles();
    void DrawChess();

    void SpeedChanges(double speed);
};
#endif // CONECTOR_ELEVADOR_WATT_H
