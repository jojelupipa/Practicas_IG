#include "../include/objeto3d_rev.h"

void Objeto3DRev::compruebaTapas(){
    double pivote = perfil_points.at(0).y;

    for(unsigned int i = 0; i < perfil_points.size(); i++){
        if(perfil_points.at(i).y >= pivote && perfil_points.at(i).x == 0){ //Si está en X=0 está en una tapa seguro
            tapa_sup = true;
            pos_tapa_sup = i;
            if(i == 0 && perfil_points.at(i).y < perfil_points.at(i+1).y && perfil_points.at(i).y < perfil_points.at(i+2).y){
                                                                            // Evitamos el caso en el que estemos ante la tapa inferior
                tapa_sup = false;                                           // en el primer punto a comprobar. Esto buscaría en los dos
                tapa_inf = true;                                            // siguientes puntos para asegurarse de que sea máximo
                pos_tapa_inf = i;
            }
        }
        if(perfil_points.at(i).y <= pivote && perfil_points.at(i).x == 0 ){ // Estudiamos si es la tapa inferior
            tapa_inf = true;
            pos_tapa_inf = i;
            if(i == 0 && perfil_points.at(i).y > perfil_points.at(i+1).y && perfil_points.at(i).y > perfil_points.at(i+2).y)
                tapa_inf = false;
        }
    }

/* Antigua implementación
    if(perfil_points.at(perfil_points.size()-2).x == 0){
        tapa_sup = true;                            // Por diseño,almacenaremos primero la tapa superior y luego la inferior
        tapa_inf = true;
        pos_tapa_sup = perfil_points.size()-2;      // Si hay una tapa en size-2 es porque hay ambas tapas
        pos_tapa_inf = perfil_points.size()-1;
    }                                               // Si queremos obtener las tapas basta con almacenar las posiciones size-2 y size-1
                                                    // en una variable de tipo _vertex3f
    else if(perfil_points.at(perfil_points.size()-1).x == 0){
        float altura_tapa = perfil_points.at(perfil_points.size()-1).y;
        float punto_cualquiera1 = perfil_points.at(perfil_points.size()-2).y;
        float punto_cualquiera2 = perfil_points.at(perfil_points.size()-3).y;
        if(altura_tapa <= punto_cualquiera1 && altura_tapa <= punto_cualquiera2){
            tapa_inf = true;
            pos_tapa_inf = perfil_points.size()-1;
        }
        else{
            tapa_sup = true;
            pos_tapa_sup = perfil_points.size()-1;
        }
    }


    // Esto se fundamenta en que si su distancia al eje de rotación es 0, será tapa, y como sólo habrá tapa superior e inferior
    // y estas se colocan al final, si su "altura" y es menor o igual que algún par de puntos cualesquiera estaremos ante la tapa inferior,
    // y en caso contrario, ante la superior.
*/
}


void Objeto3DRev::inicializaPuntos(){
    // Definimos los puntos
    int n_no_tapas = perfil_points.size();      // Queremos que el bucle guarde los puntos girados del perfil que no sean tapas
    if(tapa_sup)
        n_no_tapas--;
    if(tapa_inf)
        n_no_tapas--;



    for(int i = 0; i < NMUESTRAS; ++i){ // Para 90 muestras se puede pintar entre los ángulos deseados dividiendo por 4.
        for(int j = 0; j < n_no_tapas; ++j){
            v_points.push_back(_vertex3f(cos((i*2*M_PI)/NMUESTRAS)*perfil_points.at(j).x,perfil_points.at(j).y,sin((i*2*M_PI)/NMUESTRAS)*perfil_points.at(j).x) );
        }
    }

    if(tapa_inf){
        v_points.push_back(perfil_points.at(pos_tapa_inf)); // at (pos_tapa_inf) Tapa inferior
        inf_index = v_points.size()-1;
    }
    if(tapa_sup){
        v_points.push_back(perfil_points.at(pos_tapa_sup)); // at (pos_tapa_sup) Tapa superior
        sup_index = v_points.size()-1;
    }

}

void Objeto3DRev::inicializaTriangulos(){
    int n_puntos_sin_tapas = v_points.size();
    int perfil_size = perfil_points.size();

    if(tapa_inf){
        n_puntos_sin_tapas--;
        perfil_size--;
    }
    if(tapa_sup){
        n_puntos_sin_tapas--;
        perfil_size--;
    }

    for(int i = 0; i < n_puntos_sin_tapas; i+=1){ // Si quieres que "funcione" la esfera se cambia el 1 por el dos y viceversa

        if(i%perfil_size == 0){ // Si estamos ante una tapa superior formamos el triángulo con la tapa
            if(tapa_sup)
               v_triangulos.push_back(_vertex3i(i,(i+perfil_size)%(n_puntos_sin_tapas),sup_index)); // En el caso de haber tapa inf
            v_triangulos.push_back(_vertex3i(i,(i+perfil_size)%(n_puntos_sin_tapas),(i+1)%(n_puntos_sin_tapas)));


        }
  else if(i%perfil_size == perfil_size-1){
                v_triangulos.push_back(_vertex3i(i,(i+perfil_size)%(n_puntos_sin_tapas),(i+1)%(n_puntos_sin_tapas))); // Esto tal vez falle para figuras con mayor perfil
                if(tapa_inf)
                    v_triangulos.push_back(_vertex3i(i,(i+perfil_size)%(n_puntos_sin_tapas),inf_index)); // En el caso de haber tapa sup

        }
        else{
            v_triangulos.push_back(_vertex3i(i,(i+perfil_size)%(n_puntos_sin_tapas),(i+1)%(n_puntos_sin_tapas)));

            v_triangulos.push_back(_vertex3i((i+1+perfil_size)%n_puntos_sin_tapas,(i+perfil_size)%(n_puntos_sin_tapas),(i+1)%(n_puntos_sin_tapas)));
        }


    }

}



Objeto3DRev& Objeto3DRev::operator =(Objeto3DRev&& other) {
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
        this->perfil_points = other.perfil_points;
        this->normales_caras = other.normales_caras;
        this->normales_vertex = other.normales_vertex;
    }
    return *this;
}

Objeto3DRev& Objeto3DRev::operator =(const Objeto3DRev& other){
    if(this != &other){
        this->visible = other.visible;
        this->v_points = other.v_points;
        this->v_triangulos = other.v_triangulos;
        this->perfil_points = other.perfil_points;
        this->normales_caras = other.normales_caras;
        this->normales_vertex = other.normales_vertex;
    }
    return *this;
}



void Objeto3DRev::generador(){
    compruebaTapas();
    inicializaPuntos();
    inicializaTriangulos();
    NormalGen();
}

