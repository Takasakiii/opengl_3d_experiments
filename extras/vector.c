#include "vector.h"
#include <stdlib.h>


Vec3 vec3_create(float x, float y, float z) {
    Vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

Vec3* vec3_create_heap(float x, float y, float z) {
    Vec3* vec = (Vec3*) malloc(sizeof(Vec3));
    Vec3 created_vec = vec3_create(x, y, z);
    *vec = created_vec;
    return vec;
}


Vec3 vec3_sum(Vec3 v1, Vec3 v2) {
    return vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 vec3_mul(Vec3 v1, float k) {
    return vec3_create(v1.x * k, v1.y * k, v1.z * k);
}