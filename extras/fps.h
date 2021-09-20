#pragma once

typedef struct Fps {
    unsigned int frames;
    double last_time;
    unsigned int last_frames;
    unsigned int (*get_fps)(struct Fps* fps, double current_time);
} Fps;

Fps fps_create();
