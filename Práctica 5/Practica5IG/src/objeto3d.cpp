#include "../include/objeto3d.h"


// Práctica 4

void Objeto3D::NormalGen(){
    normales_caras.resize(v_triangulos.size()); // Habrá tantas normales como triángulos

    float x,y,z;

    for(unsigned int i = 0; i < normales_caras.size();++i){
        x = v_points.at(v_triangulos.at(i)._1).x - v_points.at(v_triangulos.at(i)._0).x;
        y = v_points.at(v_triangulos.at(i)._1).y - v_points.at(v_triangulos.at(i)._0).y;
        z = v_points.at(v_triangulos.at(i)._1).z - v_points.at(v_triangulos.at(i)._0).z;
        _vertex3f vector_A = _vertex3f(x,y,z);
        //cout << "VectorA:x: " << x << " y: " << y << " z: "<< z << endl << flush;

        x = v_points.at(v_triangulos.at(i)._2).x - v_points.at(v_triangulos.at(i)._0).x;
        y = v_points.at(v_triangulos.at(i)._2).y - v_points.at(v_triangulos.at(i)._0).y;
        z = v_points.at(v_triangulos.at(i)._2).z - v_points.at(v_triangulos.at(i)._0).z;

        _vertex3f vector_B = _vertex3f(x,y,z);
        //cout << "VectorB:x: " << x << " y: " << y << " z: "<< z << endl << flush;
        normales_caras.at(i) = vector_A.cross_product(vector_B).normalize();
        //normales_caras.at(i).show_values();


    }
    NormalVertexGen();
    //cout << "n_caras: " << v_triangulos.size() << endl;
}

void Objeto3D::NormalVertexGen(){
    normales_vertex.resize(v_points.size());
    for(unsigned int i = 0; i < normales_vertex.size();i++)
        normales_vertex.at(i) = _vertex3f(0,0,0);

    // Para cada cara sumaremos el valor de su normal a cada vértice y después normalizaremos
    // Esto será equivalente a sumar las normales de las caras que confluyen en cada vértice y normalizarlo
    for(unsigned int i = 0; i < v_triangulos.size(); i++){
        normales_vertex.at(v_triangulos.at(i)._0) += normales_caras.at(i);
        normales_vertex.at(v_triangulos.at(i)._1) += normales_caras.at(i);
        normales_vertex.at(v_triangulos.at(i)._2) += normales_caras.at(i);
    }

    for(unsigned int i = 0; i < normales_vertex.size(); i++){
        normales_vertex.at(i).normalize();
    }

}

void Objeto3D::DrawNormal(){
    glLineWidth(1.5);
    glBegin(GL_LINES);
    int n_triangulos = normales_caras.size();

    glColor3f(0,0,0);
    for(int i = 0; i < n_triangulos; ++i){
        float x,y,z;
        x = (v_points[v_triangulos[i]._0].x + v_points[v_triangulos[i]._1].x + v_points[v_triangulos[i]._2].x)/3.0;
        y = (v_points[v_triangulos[i]._0].y + v_points[v_triangulos[i]._1].y + v_points[v_triangulos[i]._2].y)/3.0;
        z = (v_points[v_triangulos[i]._0].z + v_points[v_triangulos[i]._1].z + v_points[v_triangulos[i]._2].z)/3.0;

        glVertex3f(x,y,z);
        glVertex3f(x+normales_caras.at(i).x,y+normales_caras.at(i).y,z+normales_caras.at(i).z);
    }

    for(unsigned int i = 0; i < v_points.size();i++){
        float x,y,z;
        x = v_points[i].x;
        y = v_points[i].y;
        z = v_points[i].z;

        glVertex3f(x,y,z);
        glVertex3f(x+normales_vertex.at(i).x,y+normales_vertex.at(i).y,+z+normales_vertex.at(i).z);
    }

    glEnd();
}

void Objeto3D::DrawLightFlat(int material, int angulo1, int angulo1_x, int angulo2, int angulo2_y, double position1){

    LoadMaterial(material);

    GLfloat especular2[] = { 0, 1, 0, 1.0 };
    GLfloat ambiente2[] = { 0, 1, 0, 1 };

    if(angulo1 >= 0){                   // Controlamos la disposición de la luz
        GLfloat Luz1[4]={1,0,0,1};
        glPushMatrix();
        glRotatef(angulo1, 0,1,0); // Giro de la luz sobre Y
        glRotatef(angulo1_x, 1,0,0); // Giro de la luz sobre X
        glTranslatef(position1,0,0);
        glLightfv(GL_LIGHT0,GL_POSITION,Luz1);
        glPopMatrix();
        glEnable(GL_LIGHT0);

    }

    if(angulo2 >= 0){

        GLfloat Luz2[4]={0,0,1,0};

        glPushMatrix();
        glRotatef(0, 0,1,0);
        glRotatef(angulo2, 1,0,0);
        glRotatef(angulo2_y,0,1,0);
        glLightfv(GL_LIGHT1,GL_POSITION,Luz2);
        glPopMatrix();

        glLightfv(GL_LIGHT1, GL_DIFFUSE, ambiente2);
        glLightfv(GL_LIGHT1, GL_SPECULAR, especular2);
        glEnable(GL_LIGHT1);

    }

    glShadeModel(GL_FLAT);

    glEnable(GL_LIGHTING);

    //ambiente2,espec2, light0,light2


    glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.5,0);
    int n_triangulos = v_triangulos.size();

    glColor3f(1,0,1);
    for(int i = 0; i < n_triangulos; ++i){
        glNormal3f(normales_caras.at(i).x,normales_caras.at(i).y,normales_caras.at(i).z);
        glVertex3f(v_points[v_triangulos[i]._0].x,v_points[v_triangulos[i]._0].y,v_points[v_triangulos[i]._0].z);

        glVertex3f(v_points[v_triangulos[i]._1].x,v_points[v_triangulos[i]._1].y,v_points[v_triangulos[i]._1].z);

        glVertex3f(v_points[v_triangulos[i]._2].x,v_points[v_triangulos[i]._2].y,v_points[v_triangulos[i]._2].z);
    }

    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

}

void Objeto3D::DrawLightSmooth(int material,int angulo1, int angulo1_x, int angulo2, int angulo2_y, double position1){


    LoadMaterial(material);

    // La luz 0 es blanca, pero nuestra segunda luz (GL_LIGHT1) tenemos que definirla
    GLfloat especular2[] = { 0, 1, 1, 1.0 };
    GLfloat ambiente2[] = { 0, 1, 1, 1 };

    if(angulo1 >= 0){                   // Controlamos la disposición de la luz
        GLfloat Luz1[4]={1,0,0,1};
        glPushMatrix();
        glRotatef(-angulo1_x, 1,0,0); // Giro de la luz sobre X
        glRotatef(-angulo1, 0,1,0); // Giro de la luz sobre Y

        glTranslatef(position1,0,0);
        glLightfv(GL_LIGHT0,GL_POSITION,Luz1);
        glPopMatrix();
        glEnable(GL_LIGHT0);

    }

    if(angulo2 >= 0){

        GLfloat Luz2[4]={0,0,1,0};    // Esta luz, al ser (x,y,z,w) con w != 0 está en el infinito

        glPushMatrix();
        glRotatef(0, 0,1,0);
        glRotatef(angulo2, 1,0,0);
        glRotatef(angulo2_y,0,1,0);
        glLightfv(GL_LIGHT1,GL_POSITION,Luz2);
        glTranslatef(position1,0,0); // Esto es sólo una muestra de que, al ser direccional, la distancia no influye
        glPopMatrix();

        glLightfv(GL_LIGHT1, GL_DIFFUSE, ambiente2);
        glLightfv(GL_LIGHT1, GL_SPECULAR, especular2);
        glEnable(GL_LIGHT1);

    }

    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);

    //ambiente2,espec2, light0,light2


    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    int n_triangulos = v_triangulos.size();

    glColor3f(1,0,1);
    for(int i = 0; i < n_triangulos; ++i){
        glNormal3fv((GLfloat *) &normales_vertex[v_triangulos[i].x]);
        glVertex3f(v_points[v_triangulos[i]._0].x,v_points[v_triangulos[i]._0].y,v_points[v_triangulos[i]._0].z);
        glNormal3fv((GLfloat *) &normales_vertex[v_triangulos[i].y]);
        glVertex3f(v_points[v_triangulos[i]._1].x,v_points[v_triangulos[i]._1].y,v_points[v_triangulos[i]._1].z);
        glNormal3fv((GLfloat *) &normales_vertex[v_triangulos[i].z]);
        glVertex3f(v_points[v_triangulos[i]._2].x,v_points[v_triangulos[i]._2].y,v_points[v_triangulos[i]._2].z);
    }

    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

}
void Objeto3D::LoadMaterial(int material){

    GLfloat ambiente1[4] = { 0.2f, 0.1f, 0.025f, 1.0f};
    GLfloat ambiente2[4] = {0.3f, 0.2f, 0.03,1.0f};
    GLfloat ambiente3[4] = {0.0f, 0.0f, 0.9,1.0f};

    GLfloat especular1[4] = {0.25f, 0.14f, 0.09f, 1.0f};
    GLfloat especular2[4] = {0.99f, 0.9f, 0.805f, 1.0f};
    GLfloat especular3[4] = {0.1f, 0.1f, 0.3f, 1.0f};

    GLfloat difusa1[4] = {0.7f, 0.25f, 0.07f, 1.0f };
    GLfloat difusa2[4] = {0.8f, 0.6f, 0.1f, 1.0f};
    GLfloat difusa3[4] = {0.1f, 0.2f, 0.3f, 1.0f};

    if(material == 1){
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, especular1);
        glMaterialf(GL_FRONT, GL_SHININESS,  10.0f);
    }
    else if(material == 2){

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, especular2);
        glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

    }
    else if (material == 3) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, especular3);
        glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
    }

}
