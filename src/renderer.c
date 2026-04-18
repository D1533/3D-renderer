
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "../include/renderer.h"
#include "../include/math.h"
#include "../include/config.h"

mat4_t P;

void render_object(SDL_Renderer *ren, mesh_t* obj, mat4_t view_matrix){
    
    vec2_t screen[obj->vertex_count];
    SDL_SetRenderDrawColor(ren, 255,0,0,255);
   
    for (int i = 0; i < obj->vertex_count; i++) {
        vec4_t tmp_v = vec3vec4(obj->vertices[i]);
        vec4_t model_v, view_v, projected_v;

        mat4_mul_vec4(obj->model_matrix, &tmp_v, &model_v); 
        mat4_mul_vec4(view_matrix, &model_v, &view_v);
        mat4_mul_vec4(P, &view_v, &projected_v);
        
        projected_v.x /= projected_v.w;
        projected_v.y /= projected_v.w;
        projected_v.z /= projected_v.w;
       
        screen[i].x = (int)((projected_v.x + 1.0f) * 0.5f * WINDOW_WIDTH);
        screen[i].y = (int)((1.0f - projected_v.y) * 0.5f * WINDOW_HEIGHT);

        SDL_RenderDrawPoint(ren, screen[i].x, screen[i].y);
    }

    for (int i = 0; i < obj->triangle_count; i++) {
        int a = obj->triangles[i][0];
        int b = obj->triangles[i][1];
        int c = obj->triangles[i][2];

        SDL_RenderDrawLine(ren, screen[a].x, screen[a].y, screen[b].x, screen[b].y);
        SDL_RenderDrawLine(ren, screen[b].x, screen[b].y, screen[c].x, screen[c].y);
        SDL_RenderDrawLine(ren, screen[c].x, screen[c].y, screen[a].x, screen[a].y);
    }

}

