#include "fps.h"

unsigned int fps_get_fps(Fps* fps, double current_time) {
    fps->frames++;
    if (current_time - fps->last_time >= 1.0) {
        fps->last_frames = fps->frames;
        fps->frames = 0;
        fps->last_time = current_time;
    }

    return fps->last_frames;
}


Fps fps_create() {
    Fps fps;
    fps.frames = 0;
    fps.last_time = 0;
    fps.last_frames = 0;
    fps.get_fps = fps_get_fps;
    return fps;
}
