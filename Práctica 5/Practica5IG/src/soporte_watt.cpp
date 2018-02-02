#include "../include/soporte_watt.h"

SoporteWatt::SoporteWatt(){
    cubo = Cubo();
    cilindro = CilindroPrefab();
    cabezal = CabezalWatt();
    treshold = false;
    angle = 0;
    cabezal_angle = 0;
}

SoporteWatt::SoporteWatt(const SoporteWatt &s){
    cilindro = s.cilindro;
    cubo = s.cubo;
    cabezal = s.cabezal;
    angle= s.angle;
    cabezal_angle = s.cabezal_angle;
    treshold = s.treshold;
}


void SoporteWatt::TBase(int modo){

    // Transformaciones de la base (cubo)
    glPushMatrix();
    glTranslatef(0,0.2,0);
    glScalef(5,0.4,5);
    switch (modo){
    case 1: cubo.DrawPoints();break;
    case 2: cubo.DrawLines();break;
    case 3: cubo.DrawTriangles();break;
    case 4: cubo.DrawChess();break;
    default: break;
    }
    glPopMatrix();

}

void SoporteWatt::TBarra(int modo){
    // Transformaciones de la barra (cilindro)
    glPushMatrix();
    glTranslatef(0,4,0);
    glScalef(0.4,7,0.4);
    //glRotatef(angle,0,1,0);
    GiroSobreY(angle);
    switch (modo){
    case 1: cilindro.DrawPoints();break;
    case 2: cilindro.DrawLines();break;
    case 3: cilindro.DrawTriangles();break;
    case 4: cilindro.DrawChess();break;
    default: break;
    }
    glPopMatrix();


}

void SoporteWatt::TCabezal(int modo){
    // Transformaciones del cabezal
    glPushMatrix();
    glTranslatef(0,4,0);
    glScalef(0.5,0.5,0.5);
    GiroSobreY(cabezal_angle);

    switch (modo){
    case 1: cabezal.DrawPoints();break;
    case 2: cabezal.DrawLines();break;
    case 3: cabezal.DrawTriangles();break;
    case 4: cabezal.DrawChess();break;
    default: break;
    }
    glPopMatrix();

}
void SoporteWatt::Transformaciones(int modo){
    glMatrixMode(GL_MODELVIEW);
    TBase(modo);
    TBarra(modo);
    TCabezal(modo);
}

void SoporteWatt::SwapVisible(){
    cubo.SwapVisible();
    cilindro.SwapVisible();
    cabezal.SwapVisible();
}

void SoporteWatt::DrawPoints(){
    Transformaciones(1);
}


void SoporteWatt::DrawLines(){
    Transformaciones(2);
}

void SoporteWatt::DrawTriangles(){
    Transformaciones(3);
}

void SoporteWatt::DrawChess(){
    Transformaciones(4);
}


// Rotación de la barra

void SoporteWatt::RotateBar(double angulo, double angle_2,double speed){
    angle = angulo;
    cabezal_angle = angle_2;
    cabezal.SpeedChanges(speed);
}

void SoporteWatt::SetUmbral(bool umbral){
    treshold = umbral;
}
