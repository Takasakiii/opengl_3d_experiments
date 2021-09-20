#include "camera.h"
#include <GL/glu.h>

void camera_ativar(Camera* camera) {
    Vec3 look = vec3_sum(camera->m_pos, camera->m_dir);
    gluLookAt(
        camera->m_pos.x, camera->m_pos.y, camera->m_pos.z,
        look.x, look.y, look.z,
        camera->m_up.x, camera->m_up.y, camera->m_up.z
    );
}

void camera_forward(Camera* camera) {
    camera->m_vel = vec3_mul(camera->m_dir, camera->m_scl);
    camera->m_pos = vec3_sum(camera->m_pos, camera->m_vel);
}

void camera_back(Camera* camera) {
    camera->m_vel = vec3_mul(camera->m_dir, -camera->m_scl);
    camera->m_pos = vec3_sum(camera->m_pos, camera->m_vel);
}

void camera_left(Camera* camera) {
    camera->m_vel = vec3_mul(camera->m_left, camera->m_scl);
    camera->m_pos = vec3_sum(camera->m_pos, camera->m_vel);
}

void camera_right(Camera* camera) {
    camera->m_vel = vec3_mul(camera->m_left, -camera->m_scl);
    camera->m_pos = vec3_sum(camera->m_pos, camera->m_vel);
}

Camera camera_create(Vec3 position) {
    Camera camera;
    camera.m_pos = position;
    camera.m_dir = vec3_create(0, 0, -1);
    camera.m_left = vec3_create(-1, 0, 0);
    camera.m_up = vec3_create(0, 1, 0);
    camera.m_vel = vec3_create(0, 0, 0);
    camera.m_scl = 0.5;

    camera.ativar = camera_ativar;
    camera.forward = camera_forward;
    camera.back = camera_back;
    camera.left = camera_left;
    camera.right = camera_right;
    return camera;
}