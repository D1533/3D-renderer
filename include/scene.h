#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "camera.h"
#include "object.h"
#include <stdint.h>

typedef struct{
    object_t *objects;
    size_t count;
    camera_t camera;
} scene_t;

void scene_init(scene_t *scene);
void scene_update(scene_t *scene, int mx, int my, const uint8_t *keys, float dt);
void scene_render(scene_t *scene, SDL_Renderer *ren);
#endif
