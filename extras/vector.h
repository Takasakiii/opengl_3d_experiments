#pragma once 

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3_create(float x, float y, float z);
Vec3* vec3_create_heap(float x, float y, float z);
Vec3 vec3_sum(Vec3 v1, Vec3 v2);