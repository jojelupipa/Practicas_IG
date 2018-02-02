#include "../include/vertices.h"

void Vertices::DrawPoints(){

    glPointSize(4);
    glBegin(GL_POINTS);

    int size = v_points.size();


    for(int i = 0; i < size; ++i){
        glVertex3f(v_points[i].x, v_points[i].y, v_points[i].z);
    }
    glEnd();
}
