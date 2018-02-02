#include "../include/cabezalwatt.h"


CabezalWatt::CabezalWatt(){
    elevador = Elevador();
    cilindro = CilindroPrefab();

}

void CabezalWatt::Transformaciones(int modo){
    glMatrixMode(GL_MODELVIEW);

    // Transformaciones del elevador
    glPushMatrix();
    switch (modo){
    case 1: elevador.DrawPoints();break;
    case 2: elevador.DrawLines();break;
    case 3: elevador.DrawTriangles();break;
    case 4: elevador.DrawChess();break;
    default: break;
    }
    glPopMatrix();

    // Transformaciones del cilindro cabezal
    glPushMatrix();
    glTranslatef(0,6,0);
    glScalef(3,1,3);
    switch (modo){
    case 1: cilindro.DrawPoints();break;
    case 2: cilindro.DrawLines();break;
    case 3: cilindro.DrawTriangles();break;
    case 4: cilindro.DrawChess();break;
    default: break;
    }
    glPopMatrix();
}

void CabezalWatt::SwapVisible(){
    elevador.SwapVisible();
    cilindro.SwapVisible();
}

void CabezalWatt::DrawPoints(){
    Transformaciones(1);
}


void CabezalWatt::DrawLines(){
    Transformaciones(2);
}

void CabezalWatt::DrawTriangles(){
    Transformaciones(3);
}

void CabezalWatt::DrawChess(){
    Transformaciones(4);
}


void CabezalWatt::SpeedChanges(double speed){
    elevador.SpeedChanges(speed);
}

