#ifndef OBJECT_H
#define OBJECT_H

#include "math.h"

typedef struct{
    vec3_t position;
    vec3_t rotation;
    vec3_t scale;
} transform_t;

typedef struct{
    mesh_t mesh;
    transform_t transform;
} object_t;

void object_init(object_t *obj, char *mesh_path, transform_t transform);
void object_update(object_t *obj);
#endif
