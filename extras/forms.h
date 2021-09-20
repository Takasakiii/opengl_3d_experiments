#pragma once

#include "colors.h"
#include "vector.h"

void forms_draw_rectangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Color color);
void forms_draw_cube(unsigned int opengl_id, float tamanho, Color face_colors[6]);
void forms_draw_sphere(unsigned int opengl_id, float radius, unsigned int n_stacks, unsigned int n_sectors, Color color);
void forms_draw_ground(unsigned int opengl_id, float y, Color color);