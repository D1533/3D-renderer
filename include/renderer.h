#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "math.h"
#include "obj_loader.h"


extern mat4_t P;
void render_object(SDL_Renderer *ren, mesh_t* obj, mat4_t view_matrix); 
#endif

