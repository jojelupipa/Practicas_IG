#ifndef OBJETO3D_REV_H
#define OBJETO3D_REV_H

#include "objeto3d.h"

class Objeto3DRev: public Objeto3D{
public:
    Objeto3DRev& operator =(Objeto3DRev&& other);
    Objeto3DRev& operator =(const Objeto3DRev& other);
private:
    const int NMUESTRAS = 20; // Recomendable 90

protected:
    vector<_vertex3f> perfil_points;
    bool tapa_sup;
    bool tapa_inf;
    //Posiciones en el perfil_points
    int pos_tapa_sup;
    int pos_tapa_inf;
    //Posiciones en el v_points
    int sup_index;
    int inf_index;

    /**
     * @brief generador: Genera un objeto de revolución dado un perfil
     */
    void generador();
    /**
     * @brief compruebaTapas: Método que comprueba si hay tapa inferior y superior en la figura de revolución, es necesario que se llame
     * desde los constructores de cualquier figura que use esta clase
     */
    void compruebaTapas();

    /**
     * @brief inicializaPuntos: Dado el perfil de la clase que lo use, inicializa los puntos
     **/
    void inicializaPuntos();

    /**
     * @brief inicializaTriangulos Dado el perfil genera los triángulos
     */
    void inicializaTriangulos();
};
#endif // OBJETO3D_REV_H
