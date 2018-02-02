#include "../include/triangulos.h"

void Triangulos::DrawLines(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    glBegin(GL_TRIANGLES);
    int n_triangulos = v_triangulos.size();

    glColor3f(0,0,0);
    for(int i = 0; i < n_triangulos; ++i){
        glVertex3f(v_points[v_triangulos[i]._0].x,v_points[v_triangulos[i]._0].y,v_points[v_triangulos[i]._0].z);
        glVertex3f(v_points[v_triangulos[i]._1].x,v_points[v_triangulos[i]._1].y,v_points[v_triangulos[i]._1].z);
        glVertex3f(v_points[v_triangulos[i]._2].x,v_points[v_triangulos[i]._2].y,v_points[v_triangulos[i]._2].z);
    }

    glEnd();
}

void Triangulos::DrawTriangles(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    int n_triangulos = v_triangulos.size();

    glColor3f(1,0,1);
    for(int i = 0; i < n_triangulos; ++i){
        glVertex3f(v_points[v_triangulos[i]._0].x,v_points[v_triangulos[i]._0].y,v_points[v_triangulos[i]._0].z);
        glVertex3f(v_points[v_triangulos[i]._1].x,v_points[v_triangulos[i]._1].y,v_points[v_triangulos[i]._1].z);
        glVertex3f(v_points[v_triangulos[i]._2].x,v_points[v_triangulos[i]._2].y,v_points[v_triangulos[i]._2].z);
    }


    glEnd();

}

void Triangulos::DrawChess(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    int n_triangulos = v_triangulos.size();

    glColor3f(1,0,0);
    for(int i = 0; i < n_triangulos;i+=2){
        glVertex3f(v_points[v_triangulos[i]._0].x,v_points[v_triangulos[i]._0].y,v_points[v_triangulos[i]._0].z);
        glVertex3f(v_points[v_triangulos[i]._1].x,v_points[v_triangulos[i]._1].y,v_points[v_triangulos[i]._1].z);
        glVertex3f(v_points[v_triangulos[i]._2].x,v_points[v_triangulos[i]._2].y,v_points[v_triangulos[i]._2].z);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    for(int i = 1; i < n_triangulos;i+=2){
        glVertex3f(v_points[v_triangulos[i]._0].x,v_points[v_triangulos[i]._0].y,v_points[v_triangulos[i]._0].z);
        glVertex3f(v_points[v_triangulos[i]._1].x,v_points[v_triangulos[i]._1].y,v_points[v_triangulos[i]._1].z);
        glVertex3f(v_points[v_triangulos[i]._2].x,v_points[v_triangulos[i]._2].y,v_points[v_triangulos[i]._2].z);
    }
    glEnd();

}
