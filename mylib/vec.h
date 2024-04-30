#include <stdio.h>
#include <math.h>

typedef struct 
{
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct
{
    float x;
    float y;
    float z;

} vec3;

typedef struct 
{
    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;
} mat4;

typedef struct
{
    vec3 x;
    vec3 y;
    vec3 z;

} mat3;

void vec_print(vec4 vector);
vec4 vec_scale(float scalar, vec4 vector);
vec4 vec_add(vec4 a, vec4 b);
vec4 vec_subtract(vec4 a, vec4 b);
float vec_magnitude(vec4 a);
vec4 vec_normal(vec4 a);
float vec_dot(vec4 a, vec4 b);
vec4 vec_cross(vec4 a, vec4 b);
void mat_print(mat4 a);
mat4 mat_scale(float scalar, mat4 a);
mat4 mat_add(mat4 a, mat4 b);
mat4 mat_subtract(mat4 a, mat4 b);
mat4 mat_multiply(mat4 a, mat4 b);
vec4 vec_mat_multiply(vec4 a, mat4 b);
mat4 mat_transpose(mat4 a);
int mat_invert_check(mat4 a);
mat4 mat_invert(mat4 a);
mat4 mat_minor(mat4 a);
mat4 mat_cofactor(mat4 minor);
float mat_determinant(mat4 a, mat4 m);
mat3 mat_reduce(mat4 x, int col, int row);
vec3 vec_reduce(vec4 a, int n);
float mat3_determinant(mat3 a);
mat4 translate(float x, float y, float z);
mat4 scale(float x, float y, float z);
mat4 rotate_about_x(float theta);
mat4 rotate_about_z(float theta);
mat4 rotate_about_y(float theta);
mat4 look_at(vec4 eye, vec4 at, vec4 up);
mat4 frustum(float left, float right, float bottom,
				float top, float near, float far);
mat4 identity_matrix();
