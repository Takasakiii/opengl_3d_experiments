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

Camera camera_create(Vec3 position) {
    Camera camera;
    camera.m_pos = position;
    camera.m_dir = vec3_create(0, 0, -1);
    camera.m_left = vec3_create(-1, 0, 0);
    camera.m_up = vec3_create(0, 1, 0);
    camera.ativar = camera_ativar;
    return camera;
}