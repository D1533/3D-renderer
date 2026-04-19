#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/math_utils.h"


int load_obj(const char *filename, mesh_t *mesh){

    FILE *fp = fopen(filename, "r");
    char line[512];
    
    if (fp == NULL){
        printf("Failed to open %s\n", filename);
        return -1;
    }
    
    int vertex_capacity = 128;
    int triangle_capacity = 128;

    mesh->vertices = malloc(sizeof(vec3_t)*128);
    mesh->triangles = malloc(sizeof(int[3])*128);

    int vertex_count = 0;
    int triangle_count = 0;

    while(fgets(line, sizeof(line), fp)){
        if (line[0] == 'v' && line[1] == ' '){
            if (vertex_count >= vertex_capacity){
                vertex_capacity *= 2;
                mesh->vertices = realloc(mesh->vertices, sizeof(vec3_t) * vertex_capacity);
            }
            float x,y,z;
            if (sscanf(line+2, "%f %f %f", &x, &y, &z) == 3){    
                mesh->vertices[vertex_count++] = (vec3_t){x,y,z}; 
            } 
        }
        else if ( line[0] == 'f' && line[1] == ' '){
            int i1,i2,i3;
            if (triangle_count >= triangle_capacity){
                triangle_capacity *= 2;
                mesh->triangles = realloc(mesh->triangles, sizeof(int[3]) * triangle_capacity);
            }
            if (sscanf(line + 2, "%d %d %d", &i1, &i2, &i3) == 3){
                mesh->triangles[triangle_count][0] = i1 - 1;
                mesh->triangles[triangle_count][1] = i2 - 1;
                mesh->triangles[triangle_count][2] = i3 - 1;
                triangle_count++;
            }
        }
    }

    mesh->vertex_count = vertex_count;
    mesh->triangle_count = triangle_count;
    mat4_identity(mesh->model_matrix); 
    
    return 0;
}
