#pragma once

#include "colors.h"

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3_create(float x, float y, float z);

void forms_draw_rectangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Color color);
void forms_draw_cube(unsigned int opengl_id, float tamanho, Color face_colors[6]);
void forms_draw_sphere(unsigned int opengl_id, float radius, unsigned int n_stacks, unsigned int n_sectors, Color color);
