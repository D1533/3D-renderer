#include <SDL2/SDL_keycode.h>
#include <math.h>
#include "../include/camera.h"
#include "../include/math_utils.h"
#include "../include/config.h"


void camera_rotate(camera_t *cam, int mx, int my){
    cam->yaw   += mx * CAMERA_SENSIBILITY;
    cam->pitch -= my * CAMERA_SENSIBILITY;
    
    if (cam->pitch > 1.5f) cam->pitch = 1.5f;
    if (cam->pitch < -1.5f) cam->pitch = -1.5f;
 
    cam->yaw = fmodf(cam->yaw, 2.0f * PI);
    if (cam->yaw < 0.0f)
        cam->yaw += 2.0f * PI;
}

void camera_update_basis(camera_t *cam){
    cam->forward.x = cosf(cam->pitch) * sinf(cam->yaw);
    cam->forward.y = sinf(cam->pitch);
    cam->forward.z = -cosf(cam->pitch) * cosf(cam->yaw);
    
    cam->forward = vec3_normalize(cam->forward);
    vec3_t world_up = {0, 1, 0};
    cam->right = vec3_normalize(vec3_cross(cam->forward, world_up));
    cam->up = vec3_normalize(vec3_cross(cam->right, cam->forward));
}

void camera_move(camera_t *cam, const uint8_t *keys, float dt){
    if (keys[SDL_SCANCODE_W]) 
        cam->pos = vec3_add(cam->pos, vec3_scale(cam->forward, SPEED * dt));
    if (keys[SDL_SCANCODE_S]) 
        cam->pos = vec3_sub(cam->pos, vec3_scale(cam->forward, SPEED * dt));
    if (keys[SDL_SCANCODE_A]) 
        cam->pos = vec3_sub(cam->pos, vec3_scale(cam->right, SPEED * dt)); 
    if (keys[SDL_SCANCODE_D]) 
        cam->pos = vec3_add(cam->pos, vec3_scale(cam->right, SPEED * dt)); 
}

void camera_update_view(camera_t *cam){
    
    mat4_t V;

    V[0][0] = cam->right.x;      V[0][1] = cam->right.y;      V[0][2] = cam->right.z;      V[0][3] = -(V[0][0]*cam->pos.x + V[0][1]*cam->pos.y + V[0][2]*cam->pos.z);
    V[1][0] = cam->up.x;         V[1][1] = cam->up.y;         V[1][2] = cam->up.z;         V[1][3] = -(V[1][0]*cam->pos.x + V[1][1]*cam->pos.y + V[1][2]*cam->pos.z);
    V[2][0] = -cam->forward.x;   V[2][1] = -cam->forward.y;   V[2][2] = -cam->forward.z;   V[2][3] = -(V[2][0]*cam->pos.x + V[2][1]*cam->pos.y + V[2][2]*cam->pos.z);
    V[3][0] = 0;                 V[3][1] = 0;                 V[3][2] = 0;                 V[3][3] = 1; 

    memcpy(cam->view_matrix, V, sizeof(mat4_t));
}

void camera_update(camera_t *cam, int mx, int my, const uint8_t *keys, float dt){
    camera_rotate(cam, mx, my);
    camera_update_basis(cam);
    camera_move(cam, keys, dt);
    camera_update_view(cam);
}


