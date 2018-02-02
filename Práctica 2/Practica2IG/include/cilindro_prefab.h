#ifndef CILINDRO_PREFAB_H
#define CILINDRO_PREFAB_H
#include "objeto3d_rev.h"
#include "math.h"

class CilindroPrefab:public Objeto3DRev{
private:
    const double DIST = 0.5;

public:
    CilindroPrefab();

};

#endif // CILINDRO_PREFAB_H
