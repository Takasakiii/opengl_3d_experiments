#include <vector>
#include <math.h>
#include "forms.h"

using namespace std;

vec3::vec3() {
    x = 0;
    y = 0;
    z = 0;
}

vec3::vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void rect(vec3 v1, vec3 v2, vec3 v3, vec3 v4, const color cor) {
    glColor3fv(cor);
    glBegin(GL_QUADS);
        glVertex3fv(&v1.x);
        glVertex3fv(&v2.x);
        glVertex3fv(&v3.x);
        glVertex3fv(&v4.x);
    glEnd();
}

void desenha_cubo(float tamanho) {
    float d = tamanho / 2.0;
    vec3 v1(-d, d, d);
    vec3 v2(-d, -d, d);
    vec3 v3(d, -d, d);
    vec3 v4(d, d, d);
    vec3 v5(d, d, -d);
    vec3 v6(d, -d, -d);
    vec3 v7(-d, -d, -d);
    vec3 v8(-d, d, -d);

    rect(v1, v2, v3, v4, vermelho);
    rect(v4, v3, v6, v5, azul);
    rect(v5, v8, v7, v6, amarelo);
    rect(v1, v8, v7, v2, verde);
    rect(v1, v4, v5, v8, laranja);
    rect(v2, v7, v6, v3, violeta);
}

void desenha_esfera(GLuint id, GLfloat raio, GLuint n_stacks, GLuint n_sectors) {
    vector<vector<GLuint>> indices;
    vector<vec3> pontos;
    const GLfloat PI = M_PI;
    GLfloat delta_phi = PI / n_stacks;
    GLfloat delta_theta = 2 * PI / n_sectors;
    for(GLuint i = 0; i <= n_stacks; i++) {
        GLfloat phi = - PI / 2.0 + i * delta_phi;
        GLfloat temp = raio * cos(phi);
        GLfloat y = raio * sin(phi);
        vector<GLuint> pt;

        for(GLuint j = 0; j < n_sectors; j++) {
            GLfloat theta = j * delta_theta;
            GLfloat x = temp * sin(theta);
            GLfloat z = temp * cos(theta);

            pontos.push_back(vec3(x, y, z));
            pt.push_back(pontos.size() - 1);
        }

        indices.push_back(pt);
    }

    // desenho
    // glColor3fv(vermelho);
    // glPointSize(2.5);
    // glBegin(GL_POINTS);
    // for (GLuint i = 0; i < pontos.size(); i++) {
    //     glVertex3fv(&pontos[i].x);
    // }
    // glEnd();

    glNewList(id, GL_COMPILE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
        for(GLuint i = 0; i < n_stacks; i++) {
            glBegin(GL_TRIANGLE_STRIP);

            for(GLuint j = 0; j < n_sectors; j++) {
                if(j % 2 == 0)
                    glColor3fv(vermelho);
                else
                    glColor3fv(branco);
                GLuint index = indices[i][j];
                glVertex3fv(&pontos[index].x);
                index = indices[i + 1][j];
                glVertex3fv(&pontos[index].x);
            }
        }
            
        glEnd();
    glDisable(GL_CULL_FACE);
    glEndList();
}