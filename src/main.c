
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "../include/camera.h"
#include "../include/config.h"
#include "../include/math_utils.h"
#include "../include/obj_loader.h"
#include "../include/renderer.h"
#include "../include/scene.h"

int main(void){

    SDL_Window *wd = SDL_CreateWindow("Window Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(wd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    int running = 1;
    SDL_Event e;
    
    int mx, my;
    scene_t scene;
    scene_init(&scene);
    
    uint32_t curr, last;
    last = SDL_GetTicks();
    while (running) {
        curr = SDL_GetTicks();
        float dt = (curr - last) / 1000.0f;
        last = curr;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
        }
    
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); 
        SDL_RenderClear(ren);
        
        SDL_GetRelativeMouseState(&mx, &my);
        const uint8_t* keys = SDL_GetKeyboardState(NULL);
        
        scene_update(&scene, mx, my, keys, dt);
        scene_render(&scene, ren);
                
        SDL_RenderPresent(ren);
    }

    return 0;
}

