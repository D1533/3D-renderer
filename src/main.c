
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "../include/camera.h"
#include "../include/config.h"
#include "../include/math.h"
#include "../include/obj_loader.h"
#include "../include/renderer.h"
#include "../include/scene.h"

int main(void){

    SDL_Window *wd = SDL_CreateWindow("Window Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(wd, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    SDL_Event e;
    
    mat4_projection(P, deg2rad(60.0f),(float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
    
    scene_t scene;
    scene_init(&scene);

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
        }
        
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); 
        SDL_RenderClear(ren);
        
        scene_update(&scene);
        scene_render(&scene, ren);
                
        SDL_RenderPresent(ren);
        SDL_Delay(16); // ~60 FPS
    }

    return 0;
}

