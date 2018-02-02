#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "triangulos.h"
#include "file_ply_stl.h"

class Objeto3D:public Triangulos{

private:
    /**
     * @brief NormalVertexGen: Para cada vértice se calcula su normal
     */
    void NormalVertexGen();

    _vertex4f ambiente;
    _vertex4f difusa;
    _vertex4f especular;

protected:
    bool visible;

    std::vector<_vertex3f> normales_caras;
    std::vector<_vertex3f> normales_vertex;
public:

    /**
     * @brief SwapVisible: Activa/desactiva la visibilidad del objeto3D
     */
    void SwapVisible(){visible ? visible=false:visible = true;}

    /**
     * @brief IsVisible: Devuelve si el objeto es actualmente visible
     * @return visibilidad
     */
    bool IsVisible(){return visible;}

    /**
     * @brief NormalGen: Dadas las caras de un vector de triángulos, se genera la normal de sus caras
     */
    void NormalGen();



    /**
     * @brief DrawNormal: Dibuja las normales de cada cara
     */
    void DrawNormal();

    /**
     * @brief DrawLightFlat: Dibuja la iluminación flat
     * @param material: Selecciona un material
     * @param angulo1: Ángulo de la luz 1
     * @param angulo2: Ángulo de la luz 2
     * @param position: Distancia de la luz 1 con respecto a su posición original
     */
    void DrawLightFlat(int material, int angulo1, int angulo2, double position1);

    /**
     * @brief DrawLightSmooth: Dibuja la iluminación Geroud
     * @param material: Selecciona un material
     * @param angulo1: Ángulo de la luz 1
     * @param angulo2: Ángulo de la luz 2
     * @param position: Distancia de la luz 1 con respecto a su posición original
     */
    void DrawLightSmooth(int material, int angulo1, int angulo2, double position1);
    /**
     * @brief LoadMaterial: Elige el tipo de material
     * @param kind: 1 o 2, selecciona el tipo de material de los dos disponibles
     */
    void LoadMaterial(int kind);
};


#endif // OBJETO3D_H
