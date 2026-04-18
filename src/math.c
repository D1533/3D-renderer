#include <math.h>
#include <string.h>
#include "../include/math.h"


vec4_t vec3vec4(vec3_t v){
    vec4_t w = {v.x, v.y, v.z, 1.0f};
    return w;
}
float deg2rad(float deg){
    return (deg * (PI /180.0f));
}

void mat4_mul_vec4(const mat4_t A, const vec4_t* v, vec4_t* out){
    out->x = A[0][0]*v->x + A[0][1]*v->y + A[0][2]*v->z + A[0][3]*v->w;
    out->y = A[1][0]*v->x + A[1][1]*v->y + A[1][2]*v->z + A[1][3]*v->w;
    out->z = A[2][0]*v->x + A[2][1]*v->y + A[2][2]*v->z + A[2][3]*v->w;
    out->w = A[3][0]*v->x + A[3][1]*v->y + A[3][2]*v->z + A[3][3]*v->w;
}

void mat4_mul_mat4(const mat4_t A, const mat4_t B, mat4_t result){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = 0.0f;
            for (int k = 0; k < 4; k++)
                result[i][j] += A[i][k]*B[k][j];
        }
    }
}

void mat4_identity(mat4_t A){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            A[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void mat4_rotation_x(mat4_t A, float theta){
    theta = deg2rad(theta); 
    float c = cosf(theta);
    float s = sinf(theta);

    A[0][0] = 1;    A[0][1] = 0;    A[0][2] = 0;    A[0][3] = 0;
    A[1][0] = 0;    A[1][1] = c;    A[1][2] = -s;   A[1][3] = 0;
    A[2][0] = 0;    A[2][1] = s;    A[2][2] = c;    A[2][3] = 0;
    A[3][0] = 0;    A[3][1] = 0;    A[3][2] = 0;    A[3][3] = 1;
}
void mat4_rotation_y(mat4_t A, float theta){
    theta = deg2rad(theta);
    float c = cosf(theta);
    float s = sinf(theta);

    A[0][0] = c;    A[0][1] = 0;    A[0][2] = s;    A[0][3] = 0;
    A[1][0] = 0;    A[1][1] = 1;    A[1][2] = 0;    A[1][3] = 0;
    A[2][0] = -s;   A[2][1] = 0;    A[2][2] = c;    A[2][3] = 0;
    A[3][0] = 0;    A[3][1] = 0;    A[3][2] = 0;    A[3][3] = 1;
}

void mat4_rotation_z(mat4_t A, float theta){
    theta = deg2rad(theta);
    float c = cosf(theta);
    float s = sinf(theta);

    A[0][0] = c;    A[0][1] = -s;   A[0][2] = 0;    A[0][3] = 0;
    A[1][0] = s;    A[1][1] = c;    A[1][2] = 0;    A[1][3] = 0;
    A[2][0] = 0;    A[2][1] = 0;    A[2][2] = 1;    A[2][3] = 0;
    A[3][0] = 0;    A[3][1] = 0;    A[3][2] = 0;    A[3][3] = 1;
}

void mat4_translation(mat4_t A, vec3_t t){
    A[0][0] = 1;    A[0][1] = 0;    A[0][2] = 0;    A[0][3] = t.x;
    A[1][0] = 0;    A[1][1] = 1;    A[1][2] = 0;    A[1][3] = t.y;
    A[2][0] = 0;    A[2][1] = 0;    A[2][2] = 1;    A[2][3] = t.z;
    A[3][0] = 0;    A[3][1] = 0;    A[3][2] = 0;    A[3][3] = 1;
}


void mat4_projection(mat4_t A, float fov, float aspect, float near, float far) {
    float f = 1.0f / tanf(fov / 2.0f);  

    A[0][0] = f / aspect;  A[0][1] = 0;  A[0][2] = 0;                       A[0][3] = 0;
    A[1][0] = 0;           A[1][1] = f;  A[1][2] = 0;                       A[1][3] = 0;
    A[2][0] = 0;           A[2][1] = 0;  A[2][2] = -(far + near) / (far - near);  A[2][3] = (-2 * far * near) / (far - near);
    A[3][0] = 0;           A[3][1] = 0;  A[3][2] = -1;                      A[3][3] = 0;
}


void compute_model_matrix(vec3_t rotation, vec3_t translation, vec3_t scale, mat4_t model_matrix){
    mat4_t Rx, Ry, Rz, T, S;
    
    mat4_identity(S);
    S[0][0] = scale.x;
    S[1][1] = scale.y;
    S[2][2] = scale.z;

    mat4_rotation_x(Rx, rotation.x);
    mat4_rotation_y(Ry, rotation.y);
    mat4_rotation_z(Rz, rotation.z);
    mat4_translation(T, translation);

    mat4_t Rxy, Rxyz, RxyzS;
    mat4_mul_mat4(Ry, Rx, Rxy);
    mat4_mul_mat4(Rz, Rxy, Rxyz);
    mat4_mul_mat4(Rxyz, S, RxyzS);
    mat4_mul_mat4(T, RxyzS, model_matrix);
}





























