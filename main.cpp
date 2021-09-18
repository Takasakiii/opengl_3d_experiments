#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <stdio.h>

#include "cores.h"
#include "forms.h"

#define PASSO 1.0
#define R 0.1
#define FPS 60 

static float angulo = 0;
GLuint esfera_id;

void redimensiona(int w, int h) {
    glViewport(0, 0, w, h);
    float aspect = w / (float) h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // if(w >= h) 
    //     glOrtho(-10 * aspect, 10 * aspect, -10, 10, 1, -1);
    // else
    //     glOrtho(-10, 10, -10 / aspect, 10 / aspect, 1, -1);

    gluPerspective(45, aspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);

}


void desenha() {
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(-20, 0, -50);
        glRotatef(angulo, 1, 1, 0);
        glCallList(esfera_id);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(20, 0, -50);
        glRotatef(-angulo, 1, 1, 0);
        desenha_cubo(10);
    glPopMatrix();

    angulo += 1;
}

void init() {
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    esfera_id = glGenLists(1);

    desenha_esfera(esfera_id, 7, 20, 20);
}

int main() {
    if(!glfwInit())
        return -1;
    
    GLFWwindow* window = glfwCreateWindow(900, 600, "Objetos 3d and you", NULL, NULL);

    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    init();

    double last_time = 0;
    double valor = 0;
    while(!glfwWindowShouldClose(window)) {
        double now, dt;
        

        do {
            now = glfwGetTime();
            dt = now - last_time;
        } while(dt < 1.0 / FPS);
        last_time = now;
        double velocidade = 1.0 / R * PASSO * dt;


        glfwPollEvents();
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            valor += velocidade;
            printf("%lf \n", valor);
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        redimensiona(w, h);
        desenha();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
