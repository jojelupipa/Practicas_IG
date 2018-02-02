#include "../include/tablero.h"

Tablero::Tablero(int orden){
    Size = orden+1;
    double desplazamiento = orden/2.0;

    // Inicializamos vértices
    for(int i=0; i< Size; i++)
        for(int j=0; j< Size; j++){
            v_points.push_back(_vertex3f(i-desplazamiento,j-desplazamiento,0));
        }


    //Inincializamos triángulos
    for(int i = 0; i < Size-1; i++)
        for(int j = 0; j < Size-1; j++){
            v_triangulos.push_back(_vertex3i(i*Size + j,i*Size + j +1,i*Size +j + Size));
            v_triangulos.push_back(_vertex3i(i*Size + j +1,i*Size +j + Size + 1,i*Size + j + Size));
        }

    NormalGen();

//cout <<"Vertices: " << v_points.size() << endl;
//cout <<"Orden: " << Size << endl;
//cout << "Triangulos: " << v_triangulos.size() << endl;
}

void Tablero::DrawTexture(const _vertex4f FRAME, const _vertex4f POSITION){

    // carga de una imagen
    if (image.load("../lector_imagenes_qt/imagen.png")==false)
        cout << "Image not loaded" << endl;

    // reflejo vertical
    image=image.mirrored(false,true);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // parametros de aplicacion de la textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D,0,4,image.width(),image.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,image.bits());

    /*
    int pos1 = 0;                       //Pos (0,0)
    int pos2 = v_points.size()-Size;    //Pos (1,0)
    int pos3 = v_points.size()/Size-1;  //Pos (0,1)
    int pos4 = v_points.size()-1;       //Pos (1,1)
    */

    int pos1 = POSITION._0 * Size + POSITION._1;
    int pos2 = POSITION._1 + POSITION._2 * Size;
    int pos3 = POSITION._3 + POSITION._0 * Size;
    int pos4 = POSITION._2 * Size + POSITION._3;



    glEnable(GL_TEXTURE_2D);                // Dados los vértices de las esquinas (F0,...,F3) indicamos qué se va a dibujar
    glBegin(GL_QUADS);
    glTexCoord2f(FRAME._0,FRAME._1);
    glVertex3f(v_points.at(pos1).x,v_points.at(pos1).y,0);
    glTexCoord2f(FRAME._2,FRAME._1);
    glVertex3f(v_points.at(pos2).x,v_points.at(pos2).y,0);
    glTexCoord2f(FRAME._2,FRAME._3);
    glVertex3f(v_points.at(pos4).x,v_points.at(pos4).y,0);
    glTexCoord2f(FRAME._0,FRAME._3);
    glVertex3f(v_points.at(pos3).x,v_points.at(pos3).y,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}




Tablero& Tablero::operator =(Tablero&& other) {
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
        this->normales_caras = other.normales_caras;
        this->normales_vertex = other.normales_vertex;
        this->Size = other.Size;
        this->image = other.image;
    }
    return *this;
}

Tablero& Tablero::operator =(const Tablero& other){
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
        this->normales_caras = other.normales_caras;
        this->normales_vertex = other.normales_vertex;
        this->Size = other.Size;
        this->image = other.image;
    }
    return *this;
}
