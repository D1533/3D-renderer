
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "../include/renderer.h"
#include "../include/camera.h"
#include "../include/math.h"
#include "../include/config.h"


void render_object(SDL_Renderer *ren, mesh_t* obj, camera_t *camera){
    
    vec2_t screen[obj->vertex_count];
    SDL_SetRenderDrawColor(ren, 255,0,0,255);
    uint8_t valid[obj->vertex_count];
    memset(valid, 0, sizeof(valid));  
    for (int i = 0; i < obj->vertex_count; i++) {
        vec4_t tmp_v = vec3vec4(obj->vertices[i]);
        vec4_t model_v, view_v, projected_v;

        mat4_mul_vec4(obj->model_matrix, &tmp_v, &model_v); 
        mat4_mul_vec4(camera->view_matrix, &model_v, &view_v);
        
        if (view_v.z > -0.1f)
            continue;

        mat4_mul_vec4(camera->projection_matrix, &view_v, &projected_v);
        
        if (fabsf(projected_v.w) < 0.00001f)
            continue;
        valid[i] = 1;
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
        
        if (!valid[a] || !valid[b] || !valid[c])
            continue;

        SDL_RenderDrawLine(ren, screen[a].x, screen[a].y, screen[b].x, screen[b].y);
        SDL_RenderDrawLine(ren, screen[b].x, screen[b].y, screen[c].x, screen[c].y);
        SDL_RenderDrawLine(ren, screen[c].x, screen[c].y, screen[a].x, screen[a].y);
    }

}

