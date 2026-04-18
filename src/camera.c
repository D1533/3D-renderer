#include <SDL2/SDL_keycode.h>
#include <math.h>
#include "../include/camera.h"
#include "../include/math.h"

void camera_handle_input(camera_t *cam, const Uint8 *keys){
    if (keys[SDL_SCANCODE_W]) cam->pos.z += cam->forward.z * 0.1f;
    if (keys[SDL_SCANCODE_S]) cam->pos.z -= cam->forward.z * 0.1f;
    if (keys[SDL_SCANCODE_A]) cam->pos.x -= cam->right.x * 0.1f;
    if (keys[SDL_SCANCODE_D]) cam->pos.x += cam->right.x * 0.1f;
}

void update_view(camera_t *cam){
    mat4_t V;

    cam->forward.x = cosf(cam->pitch) * sinf(cam->yaw);
    cam->forward.y = sinf(cam->pitch);
    cam->forward.z = -cosf(cam->pitch) * cosf(cam->yaw);

    cam->right.x = cam->forward.z;
    cam->right.y = 0;
    cam->right.z = -cam->forward.x;

    cam->up.x = cam->forward.y * cam->right.z - cam->forward.z * cam->right.y;
    cam->up.y = cam->forward.z * cam->right.x - cam->forward.x * cam->right.z;
    cam->up.z = cam->forward.x * cam->right.y - cam->forward.y * cam->right.x;

    V[0][0] = cam->right.x;      V[0][1] = cam->right.y;      V[0][2] = cam->right.z;      V[0][3] = -(V[0][0]*cam->pos.x + V[0][1]*cam->pos.y + V[0][2]*cam->pos.z);
    V[1][0] = cam->up.x;         V[1][1] = cam->up.y;         V[1][2] = cam->up.z;         V[1][3] = -(V[1][0]*cam->pos.x + V[1][1]*cam->pos.y + V[1][2]*cam->pos.z);
    V[2][0] = -cam->forward.x;   V[2][1] = -cam->forward.y;   V[2][2] = -cam->forward.z;   V[2][3] = -(V[2][0]*cam->pos.x + V[2][1]*cam->pos.y + V[2][2]*cam->pos.z);
    V[3][0] = 0;            V[3][1] = 0;            V[3][2] = 0;            V[3][3] = 1; 

    memcpy(cam->view_matrix, V, sizeof(mat4_t));
}

