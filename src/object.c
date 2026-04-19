#include "../include/math_utils.h"
#include "../include/object.h"
#include "../include/obj_loader.h"


void object_init(object_t *obj, char *mesh_path, transform_t transform){
    load_obj(mesh_path, &obj->mesh);
    obj->transform = transform;
}

void object_update(object_t *obj){
    obj->transform.rotation.y += 1; 
    compute_model_matrix(obj->transform.rotation, 
                        obj->transform.position, 
                        obj->transform.scale,
                        &obj->mesh.model_matrix);
}
