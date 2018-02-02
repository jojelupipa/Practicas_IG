#include "../include/brazo_watt.h"

BrazoWatt::BrazoWatt(){
    esfera = Sphere();
    cilindro = CilindroPrefab();
    angle = 0;
    offset_cilindro = 0;
    offset_esfera = 0;
    offset_conector = 0;
}

BrazoWatt::BrazoWatt(const BrazoWatt &brazo){
    esfera = brazo.esfera;
    cilindro=brazo.cilindro;
    conector = brazo.conector;
    angle = brazo.angle;
    offset_conector = brazo.offset_conector;
    offset_cilindro = brazo.offset_cilindro;
    offset_esfera = brazo.offset_esfera;
}

void BrazoWatt::Transformaciones(int modo){

    //Transformaciones Esfera
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(4+0.75*offset_esfera,1+offset_esfera,0);// Coloca la esfera en su lugar
    glRotatef(90+angle,1,0,0); // Pone la esfera en vertical
    switch (modo){
    case 1: esfera.DrawPoints();break;
    case 2: esfera.DrawLines();break;
    case 3: esfera.DrawTriangles();break;
    case 4: esfera.DrawChess();break;
    default: break;
    }
    glPopMatrix();

    // Transformaciones Cilindro que une Esfera y cabezal
    glPushMatrix();
    glTranslatef(2+offset_cilindro,3.5+offset_cilindro,0);      // Se pone en su posición
    glRotatef(45+angle,0,0,1);        // Rota 45 grados
    glScalef(0.3,5,0.3);        // Se ajusta al tamaño adecuado
    switch (modo){
    case 1: cilindro.DrawPoints();break;
    case 2: cilindro.DrawLines();break;
    case 3: cilindro.DrawTriangles();break;
    case 4: cilindro.DrawChess();break;
    default: break;
    }
    glPopMatrix();

    // Conector Elevador
    glPushMatrix();
    glTranslatef(0,offset_conector,0);
    switch (modo){
    case 1: conector.DrawPoints();break;
    case 2: conector.DrawLines();break;
    case 3: conector.DrawTriangles();break;
    case 4: conector.DrawChess();break;
    default: break;
    }
    glPopMatrix();
}

void BrazoWatt::DrawPoints(){
    Transformaciones(1);
}

void BrazoWatt::SwapVisible(){
    esfera.SwapVisible();
    cilindro.SwapVisible();
    conector.SwapVisible();
}

void BrazoWatt::DrawLines(){
    Transformaciones(2);
}

void BrazoWatt::DrawTriangles(){
    Transformaciones(3);
}

void BrazoWatt::DrawChess(){
    Transformaciones(4);
}

void BrazoWatt::SpeedChanges(double speed){
    if (speed > 20)
        speed = 20;

    if (speed >= 3){
        angle = (speed-3)/0.44;
        offset_cilindro =(speed-3)/15.0; // offset del cilindro
        offset_esfera =(speed-3)/6.0; // offset de la efera
        offset_conector = (speed -3)/5.0;
    }
    conector.SpeedChanges(speed);
}
