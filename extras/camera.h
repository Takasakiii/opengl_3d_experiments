#pragma onde

#include "vector.h"

typedef struct Camera {
    Vec3 m_pos;
    Vec3 m_dir;
    Vec3 m_left;
    Vec3 m_up;
    Vec3 m_vel;
    float m_scl;

    void (*ativar)(struct Camera* camera);

    void (*forward)(struct Camera* camera);
    void (*back)(struct Camera* camera);
    void (*left)(struct Camera* camera);
    void (*right)(struct Camera* camera);
} Camera;

Camera camera_create(Vec3 position);