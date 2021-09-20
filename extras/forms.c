#include "forms.h"

#include <GLFW/glfw3.h>
#include <collectc/cc_array.h>

#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

#define GROUND_L 500
#define GROUD_INCREMENT 1.0


void forms_draw_rectangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Color color) {
    glColor3fv(&color.r);
    glBegin(GL_QUADS);
        glVertex3fv(&v1.x);
        glVertex3fv(&v2.x);
        glVertex3fv(&v3.x);
        glVertex3fv(&v4.x);
    glEnd();
}

void forms_draw_cube(unsigned int opengl_id, float tamanho, Color face_colors[6]) {
    float d = tamanho / 2.0;

    Vec3 v1 = vec3_create(-d, d, d);
    Vec3 v2 = vec3_create(-d, -d, d);
    Vec3 v3 = vec3_create(d, -d, d);
    Vec3 v4 = vec3_create(d, d, d);
    Vec3 v5 = vec3_create(d, d, -d);
    Vec3 v6 = vec3_create(d, -d, -d);
    Vec3 v7 = vec3_create(-d, -d, -d);
    Vec3 v8 = vec3_create(-d, d, -d);

    glNewList(opengl_id, GL_COMPILE);
        forms_draw_rectangle(v1, v2, v3, v4, face_colors[0]);
        forms_draw_rectangle(v4, v3, v6, v5, face_colors[1]);
        forms_draw_rectangle(v5, v8, v7, v6, face_colors[2]);
        forms_draw_rectangle(v1, v8, v7, v2, face_colors[3]);
        forms_draw_rectangle(v1, v4, v5, v8, face_colors[4]);
        forms_draw_rectangle(v2, v7, v6, v3, face_colors[5]);
    glEndList();    
}

void forms_draw_sphere(unsigned int opengl_id, float radius, unsigned int n_stacks, unsigned int n_sectors, Color color) {
    CC_Array* indices;
    CC_Array* pontos;

    cc_array_new(&indices);
    cc_array_new(&pontos);

    float delta_phi = PI / n_stacks;
    float delta_theta = 2 * PI / n_sectors;

    for(unsigned int i = 0; i <= n_stacks; i++) {
        float phi = - PI / 2.0 + i * delta_phi;
        float temp = radius * cosf(phi);
        float y = radius * sinf(phi);

        CC_Array* pt;
        cc_array_new(&pt);

        for(unsigned int j = 0; j < n_sectors; j++) {
            float theta = j * delta_theta;
            float x = temp * sinf(theta);
            float z = temp * cosf(theta);

            Vec3* ponto = vec3_create_heap(x, y, z);
            cc_array_add(pontos, ponto);
            unsigned long* ponto_index = malloc(sizeof(unsigned long));
            *ponto_index = (unsigned long)cc_array_size(pontos) - 1;
            cc_array_add(pt, (void*) ponto_index);
        }

        cc_array_add(indices, pt);
    }

    glNewList(opengl_id, GL_COMPILE);
        glColor3fv(&color.r);
        glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);

            for(unsigned int i = 0; i < n_stacks; i++) {
                glBegin(GL_TRIANGLE_STRIP);
                for(unsigned int j = 0; j < n_sectors; j++) {
                    CC_Array* pt_array;
                    cc_array_get_at(indices, i, (void*) &pt_array);
                    unsigned long* index;
                    cc_array_get_at(pt_array, j, (void*) &index);
                    Vec3* vertice;
                    cc_array_get_at(pontos, *index, (void*) &vertice);
                    glVertex3fv(&vertice->x);
                    
                    cc_array_get_at(indices, i + 1, (void*) &pt_array);
                    cc_array_get_at(pt_array, j, (void*) &index);
                    cc_array_get_at(pontos, *index, (void*) &vertice);
                    glVertex3fv(&vertice->x);
                }
            }

            glEnd();
        glDisable(GL_CULL_FACE);
    glEndList();

    for (unsigned int i = 0; i < cc_array_size(indices); i++) {
        CC_Array* pt;
        cc_array_get_at(indices, i, (void*) &pt);
        for (unsigned int j = 0; j < cc_array_size(pt); j++) {
            unsigned int* index;
            cc_array_get_at(pt, j, (void*) &index);
            free(index);
        }
        cc_array_destroy(pt);
    }

    cc_array_destroy(indices);

    for (unsigned int i = 0; i < cc_array_size(pontos); i++) {
        Vec3* ponto;
        cc_array_get_at(pontos, i, (void*) &ponto);
        free(ponto);
    }

    cc_array_destroy(pontos);

}

void forms_draw_ground(unsigned int opengl_id, float y, Color color) {
    glNewList(opengl_id, GL_COMPILE);
        glColor3fv(&color.r);
        glBegin(GL_LINES);
            for(float i = -GROUND_L; i <= GROUND_L; i += GROUD_INCREMENT) {
                glVertex3f(i, y, -GROUND_L);
                glVertex3f(i, y, GROUND_L);

                glVertex3f(-GROUND_L, y, i);
                glVertex3f(GROUND_L, y, i);
            }
        glEnd();
    glEndList();
}