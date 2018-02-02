#include "../include/conector_elevador_watt.h"

ConectorElevadorWatt::ConectorElevadorWatt(){
    cilindro = CilindroPrefab();
    offset = 0;
    angle = 0;
}

ConectorElevadorWatt::ConectorElevadorWatt(const ConectorElevadorWatt &c){
    cilindro = c.cilindro;
    offset = c.offset;
    angle = c.angle;
}

void ConectorElevadorWatt::Transformaciones(int modo){
    // Transformaciones Cilindro que une el elevador con el otro cilindro del brazo
    glPushMatrix();
    glTranslatef(1.7,1.7-offset,0);
    glRotatef(-45-angle*0.7,0,0,1);
    glScalef(0.3,3,0.3);
    switch (modo){
    case 1: cilindro.DrawPoints();break;
    case 2: cilindro.DrawLines();break;
    case 3: cilindro.DrawTriangles();break;
    case 4: cilindro.DrawChess();break;
    default: break;
    }
    glPopMatrix();
}


void ConectorElevadorWatt::DrawPoints(){
    Transformaciones(1);
}

void ConectorElevadorWatt::SwapVisible(){
    cilindro.SwapVisible();
}

void ConectorElevadorWatt::DrawLines(){
    Transformaciones(2);
}

void ConectorElevadorWatt::DrawTriangles(){
    Transformaciones(3);
}

void ConectorElevadorWatt::DrawChess(){
    Transformaciones(4);
}

void ConectorElevadorWatt::SpeedChanges(double speed){
    if (speed > 20)
        speed = 20;

    if (speed >= 3){
        angle = (speed-3)/0.44;
        offset = (speed-3)/17.0;
    }

}
