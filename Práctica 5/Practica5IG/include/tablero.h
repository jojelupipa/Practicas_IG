#ifndef TABLERO_H
#define TABLERO_H
#include "objeto3d.h"
#include <cmath>
#include "qimage.h"

class Tablero:public Objeto3D{

private:
    const int PROPORTIONS= 2;
    int Size;
    int max_fils_allowed;
    int max_cols_allowed;
    QImage image;
public:

    /**
     * @brief Tablero: Constructor dado un orden del objeto tablero
     * @param orden: Orden de la matriz que representará los vértices del tablero
     */
    Tablero(int orden);

    Tablero(int filas,int columnas);
    Tablero(){}

    /**
     * @brief DrawTexture: Dibuja la textura
     * @param FRAME: Es un vector de cuatro flotantes, comprendidos entre 0 y 1 que delimitarán la región de la imagen original a dibujar en
     *               el tablero
     * @param POSITION: Vector que representa la posición en la que se pintará el frame que se define en el parámetro anterior
     */
    void DrawTexture(const _vertex4f FRAME, const _vertex4f POSITION);

    int getSize() {return Size;}
    int getMaxFilsAllowed(){return max_fils_allowed;}
    int getMaxColsAllowed(){return max_cols_allowed;}



    Tablero& operator =(Tablero&& other);
    Tablero& operator =(const Tablero& other);
};
#endif // TABLERO_H
