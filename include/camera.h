#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"

typedef struct {
    vec3_t pos;
    vec3_t forward;
    vec3_t right;
    vec3_t up;

    float yaw;
    float pitch;

    mat4_t view_matrix;
} camera_t;

void camera_update(camera_t *cam);
#endif
