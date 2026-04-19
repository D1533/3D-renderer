#ifndef CAMERA_H
#define CAMERA_H

#include "math_utils.h"
#include <stdint.h>

typedef struct {
    vec3_t pos;
    vec3_t forward;
    vec3_t right;
    vec3_t up;

    float yaw;
    float pitch;

    mat4_t view_matrix;
    mat4_t projection_matrix;
} camera_t;

void camera_rotate(camera_t *cam, int mx, int my);
void camera_update_basis(camera_t *cam);
void camera_move(camera_t *cam, const uint8_t *keys, float dt);
void camera_update_view(camera_t *cam);
void camera_update(camera_t *cam, int mx, int my, const uint8_t *keys, float dt);
#endif
