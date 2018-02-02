#ifndef ELEVADOR_H
#define ELEVADOR_H
#include "brazo_watt.h"
#include "cubo.h"

class Elevador{
private:
    BrazoWatt brazo;
    CilindroPrefab cilindro;
    Cubo cubo;
    double offset_y;
    void Transformaciones(int modo);

public:
    Elevador();
    Elevador(const Elevador& el);

    void SwapVisible();
    void DrawPoints();
    void DrawLines();
    void DrawTriangles();
    void DrawChess();

    void SpeedChanges(double speed);
};
#endif // ELEVADOR_H
