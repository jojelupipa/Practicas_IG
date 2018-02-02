#include "../include/elevador.h"

Elevador::Elevador(){
    brazo = BrazoWatt();
    cilindro = CilindroPrefab();
    cubo = Cubo();
    offset_y = 0;
}

Elevador::Elevador(const Elevador &el){
    brazo = el.brazo;
    cilindro = el.cilindro;
    cubo = el.cubo;
    offset_y = el.offset_y;
}

void Elevador::Transformaciones(int modo){
    glMatrixMode(GL_MODELVIEW);
    //Transformaciones de la varilla (cubo)
    glPushMatrix();
    glTranslatef(-1,-1.5+offset_y,0);
    glScalef(0.3,5,0.3);
    switch (modo) {
    case 1:cubo.DrawPoints();break;
    case 2:cubo.DrawLines();break;
    case 3:cubo.DrawTriangles();break;
    case 4:cubo.DrawChess();break;
    default:break;
    }
    glPopMatrix();

    // Transformaciones en el cilindro
    glPushMatrix();
    glTranslatef(0,1.5+offset_y,0);
    glScalef(3,1,3);
    switch (modo) {
    case 1:cilindro.DrawPoints();break;
    case 2:cilindro.DrawLines();break;
    case 3:cilindro.DrawTriangles();break;
    case 4:cilindro.DrawChess();break;
    default:break;
    }
    glPopMatrix();

    // Transformaciones en los brazos
    // Primer brazo
    glPushMatrix();
    glTranslated(0.9,1,0);
    switch (modo) {
    case 1:brazo.DrawPoints();break;
    case 2:brazo.DrawLines();break;
    case 3:brazo.DrawTriangles();break;
    case 4:brazo.DrawChess();break;
    default:break;
    }
    glPopMatrix();

    // Segundo Brazo
    glPushMatrix();
    glTranslatef(-0.9,1,0);
    glRotatef(180,0,1,0);
    switch (modo) {
    case 1:brazo.DrawPoints();break;
    case 2:brazo.DrawLines();break;
    case 3:brazo.DrawTriangles();break;
    case 4:brazo.DrawChess();break;
    default:break;
    }
    glPopMatrix();
}

void Elevador::SwapVisible(){
    brazo.SwapVisible();
    cilindro.SwapVisible();
    cubo.SwapVisible();
}

void Elevador::DrawPoints(){
    Transformaciones(1);
}


void Elevador::DrawLines(){
    Transformaciones(2);
}

void Elevador::DrawTriangles(){
    Transformaciones(3);
}

void Elevador::DrawChess(){
    Transformaciones(4);
}

void Elevador::SpeedChanges(double speed){
    if (speed > 20)
        speed = 20; // Ajustamos tope de velocidad

    if(speed >= 3){
        offset_y = (speed-3)/5.0 ;
    }

    brazo.SpeedChanges(speed);

}
