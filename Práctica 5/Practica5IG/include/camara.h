#ifndef CAMARA_H
#define CAMARA_H

class Camara{

private:
    float xDistance;
    float yDistance;
    float zDistance;
    float xAngle;
    float yAngle;

public:
    Camara(){}

    Camara(float xDist, float yDist, float zDist, float xAng, float yAng){
        xDistance = xDist;
        yDistance = yDist;
        zDistance = zDist;
        xAngle = xAng;
        yAngle = yAng;
    }

    float getxDist(){return xDistance;}
    float getyDist(){return yDistance;}
    float getzDist(){return zDistance;}
    float getxAngle(){return xAngle;}
    float getyAngle(){return yAngle;}
};
#endif // CAMARA_H
