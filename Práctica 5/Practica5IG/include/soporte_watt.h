#ifndef SOPORTE_H
#define SOPORTE_H
#include "cabezalwatt.h"

class SoporteWatt{
private:
    CilindroPrefab cilindro;
    Cubo cubo;
    CabezalWatt cabezal;
    double angle;
    double cabezal_angle;
    bool treshold;

    // Por cada variable añadida hay que añadirla al constructor copia

    void Transformaciones(int modo);
    void TBase(int modo);
    void TBarra(int modo);
    void TCabezal(int modo);
    /**
     * @brief GiroSobreY: Mete en la pila un giro de un ángulo determinado
     * @param angle: Ángulo a girar.
     */
    void GiroSobreY(double angle){glRotatef(angle,0,1,0);}

public:
    SoporteWatt();
    SoporteWatt(const SoporteWatt& s);

    void SwapVisible();
    void DrawPoints();
    void DrawLines();
    void DrawTriangles();
    void DrawChess();
    void DrawLight();

    void RotateBar(double angulo, double angle_2, double speed);
    void SetUmbral(bool umbral);

};

#endif // SOPORTE_H
