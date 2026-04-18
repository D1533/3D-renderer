#ifndef MATH_H
#define MATH_H

#define PI 3.14159265358979323846

typedef float mat4_t[4][4];

typedef struct{
    float x,y;
} vec2_t;

typedef struct{
    float x,y,z;
} vec3_t;

typedef struct{
    float x,y,z,w;
} vec4_t;

typedef struct{
    vec3_t* vertices;
    int vertex_count;

    int (*triangles)[3];
    int triangle_count;

    mat4_t model_matrix;
} mesh_t;

float deg2rad(float deg);

vec4_t vec3vec4(vec3_t v);
void mat4_identity(mat4_t A);
void mat4_mul_vec4(const mat4_t A, const vec4_t* v, vec4_t* out);
void mat4_mul_mat4(const mat4_t A, const mat4_t B, mat4_t result);

void mat4_rotation_x(mat4_t A, float theta);
void mat4_rotation_y(mat4_t A, float theta);
void mat4_rotation_z(mat4_t A, float theta);
void mat4_translation(mat4_t A, vec3_t t);
void mat4_projection(mat4_t A, float fov, float aspect, float near, float far);

void compute_model_matrix(vec3_t rotation, vec3_t translation, vec3_t scale, mat4_t model_matrix);

#endif
