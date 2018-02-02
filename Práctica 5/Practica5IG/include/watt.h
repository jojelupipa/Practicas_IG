#ifndef WATT_H
#define WATT_H
#include "objeto3d.h" // Tendré que cambiarlo por el de alguna figura que use
#include "cubo.h"

class Watt:public Objeto3D{
private:
    Cubo base;

public:
    /**
     * @brief Watt: Constructor estándar del objeto regulador Watt
     */
    Watt();

    /**
     * @brief Draw: Se encarga de dibujar todo el objeto
     */
    //Draw();

};

#endif // WATT_H
