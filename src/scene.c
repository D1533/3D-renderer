#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "../include/math.h"
#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/object.h"
#include "../include/config.h"

void scene_init(scene_t *scene){
    scene->count = 2;
    scene->objects = malloc(sizeof(object_t) * scene->count);
    transform_t transform;
    
    transform.position = (vec3_t){0, 0, -20};
    transform.rotation = (vec3_t){0, 1, 0};
    transform.scale = (vec3_t){3, 3, 3};
    object_init(&scene->objects[0], "../assets/sphere.obj", transform); 
    
    transform.position = (vec3_t){2, 2, -5};
    transform.rotation = (vec3_t){0, 1, 0};
    transform.scale = (vec3_t){1, 1, 1};
    object_init(&scene->objects[1], "../assets/sphere.obj", transform); 
    
    camera_t cam = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},0,0};
    mat4_identity(cam.view_matrix);
    mat4_projection(cam.projection_matrix, deg2rad(60.0f),(float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
    
    scene->camera = cam;
}

void scene_update(scene_t *scene){

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    camera_handle_input(&scene->camera, keys);
    update_view(&scene->camera); 
    
    for (size_t i = 0; i < scene->count; i++){
        object_update(&scene->objects[i]);
    }

}

void scene_render(scene_t *scene, SDL_Renderer *ren){
    for (size_t i = 0; i < scene->count; i++){
        render_object(ren, &scene->objects[i].mesh, scene->camera);
    }
}
