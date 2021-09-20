#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <stdio.h>

#include "extras/fps.h"
#include "extras/forms.h"

#define PASSO_PER_FRAME 60.0

typedef struct {
    unsigned int esfera_1_id;
    unsigned int cubo_1_id;
    unsigned int esfera_2_id;
} OpenGlObjectsIds;

typedef struct {
    OpenGlObjectsIds opengl_objects;
    float angulo_rotacao;
} State;

static State app_state;

void set_fps_title(Fps* fps, GLFWwindow* window, double current_time) {
    char new_title[27];
    unsigned int current_fps = fps->get_fps(fps, current_time);
    sprintf(new_title, "Objetos 3D and You - %d FPS", current_fps);
    glfwSetWindowTitle(window, new_title);
}

void inicialize_objects() {
    Color cube_face_colors[6];
    cube_face_colors[0] = color_laranja();
    cube_face_colors[1] = color_verde();
    cube_face_colors[2] = color_vermelho();
    cube_face_colors[3] = color_violeta();
    cube_face_colors[4] = color_cinza();
    cube_face_colors[5] = color_preto();
    forms_draw_cube(app_state.opengl_objects.cubo_1_id, 10, cube_face_colors);

    forms_draw_sphere(app_state.opengl_objects.esfera_1_id, 5, 50, 50, color_verde());
    forms_draw_sphere(app_state.opengl_objects.esfera_2_id, 5, 50, 50, color_preto());
}

void init() {
    unsigned int first_alocated_id = glGenLists(3);
    app_state.opengl_objects.esfera_1_id = first_alocated_id;
    app_state.opengl_objects.cubo_1_id = first_alocated_id + 1;
    app_state.opengl_objects.esfera_2_id = first_alocated_id + 2;

    app_state.angulo_rotacao = 0;

    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void update_window(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = width / (float) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 0.1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw(double dt) {
    double velocidade_angular = PASSO_PER_FRAME * dt;

    glPushMatrix();
        glTranslatef(-20, 0, -50);
        glRotatef(app_state.angulo_rotacao, 1, 1, 0);
        glCallList(app_state.opengl_objects.cubo_1_id);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -60);
        glRotatef(app_state.angulo_rotacao, 1, 1, 0);
        glCallList(app_state.opengl_objects.esfera_1_id);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(20, 0, -50);
        glRotatef(app_state.angulo_rotacao, 1, 1, 0);
        glCallList(app_state.opengl_objects.esfera_2_id);
    glPopMatrix();

    app_state.angulo_rotacao += 1;    
}

int main() {
    if(!glfwInit())
        return -1;
    
    GLFWwindow* window = glfwCreateWindow(900, 600, "Objetos 3D and You", NULL, NULL);

    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    init();
    inicialize_objects();
    Fps fps = fps_create();

    while(!glfwWindowShouldClose(window)) {
        double current_time = glfwGetTime();
        set_fps_title(&fps, window, current_time);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        update_window(window);

        draw(0);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}