#ifndef CONO_H
#define CONO_H
#include "objeto3d_rev.h"

class Cono:public Objeto3DRev{
private:
    const double DIST = 0.5;
    void inicializaTriangulos();
public:
    Cono();
};

#endif // CONO_H
