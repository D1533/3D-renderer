#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "math_utils.h"
#include "obj_loader.h"
#include "camera.h"

extern mat4_t P;
void render_object(SDL_Renderer *ren, mesh_t *obj, camera_t *camera); 
#endif

