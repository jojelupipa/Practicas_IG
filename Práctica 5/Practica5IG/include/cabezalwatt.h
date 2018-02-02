#ifndef CABEZALWATT_H
#define CABEZALWATT_H
#include "elevador.h"

class CabezalWatt{
  private:
    Elevador elevador;
    CilindroPrefab cilindro;
    void Transformaciones(int modo);

public:

    CabezalWatt();
    CabezalWatt(const CabezalWatt& c){elevador = c.elevador; cilindro = c.cilindro;}

    void SwapVisible();
    void DrawPoints();
    void DrawLines();
    void DrawTriangles();
    void DrawChess();

    /**
     * @brief SpeedChanges: Cambios en función de la velocidad que sufre el cabezal.
     * @param speed: Velocidad de giro
     */
    void SpeedChanges(double speed);

};

#endif // CABEZALWATT_H
