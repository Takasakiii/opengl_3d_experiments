#pragma onde

#include "vector.h"

typedef struct Camera {
    Vec3 m_pos;
    Vec3 m_dir;
    Vec3 m_left;
    Vec3 m_up;

    void (*ativar)(struct Camera* camera);
} Camera;

Camera camera_create(Vec3 position);