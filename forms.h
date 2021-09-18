#pragma once
#include <GLFW/glfw3.h>
#include "cores.h"

struct vec3
{
    float x;
    float y;
    float z;

    vec3();
    vec3(float x, float y, float z);
};

void rect(vec3 v1, vec3 v2, vec3 v3, vec3 v4, const color cor);

void desenha_cubo(float tamanho);

void desenha_esfera(GLuint id, GLfloat raio, GLuint n_stacks, GLuint n_sectors);