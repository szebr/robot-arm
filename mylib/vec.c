#include "vec.h"
#include <stdio.h>
#include <math.h>

// simple printout of the vector "[1, 2, 3, 4]"
void vec_print(vec4 vector)
{
    printf("[%.2f, %.2f, %.2f, %.2f]\n", 
        vector.x, vector.y, vector.z, vector.w);
}

// this vector uses multiplication to scale each value in the vector
// by a floating point number provided in the arguments.
vec4 vec_scale(float scalar, vec4 vector)
{
    vec4 scaled;
    scaled.x = (scalar * vector.x);
    scaled.y = (scalar * vector.y);
    scaled.z = (scalar * vector.z);
    scaled.w = (scalar * vector.w);
    return scaled;
}

// this function uses simple math to add two vectors together
// going value-by-value and adding them into a new vector struct
vec4 vec_add(vec4 a, vec4 b)
{
    vec4 scaled;
    scaled.x = (a.x + b.x);
    scaled.y = (a.y + b.y);
    scaled.z = (a.z + b.z);
    scaled.w = (a.w + b.w);
    return scaled;
}

// this function uses some simple math to subtract the corresponding values
// of each vector from each other and returns a new modified vector
vec4 vec_subtract(vec4 a, vec4 b)
{
    vec4 scaled;
    scaled.x = (a.x - b.x);
    scaled.y = (a.y - b.y);
    scaled.z = (a.z - b.z);
    scaled.w = (a.w - b.w);
    return scaled;
}

// the magnitude of a vector = the square root of the dot product of the vector
float vec_magnitude(vec4 a)
{
    return sqrt(vec_dot(a,a));
}

vec4 vec_normal(vec4 a)
{
    float one = 1.0;
    return vec_scale((one/vec_magnitude(a)), a);
}

// this vector uses some simple math to find the dot product between
// the two. it simply multiplies each value in each vector by the corresponding
// value in the other vector, and adds them all up.
float vec_dot(vec4 a, vec4 b)
{
    return ((a.x * b.x) +
            (a.y * b.y) +
            (a.z * b.z) +
            (a.w * b.w));
}

// this function finds the cross product using the formula
// listed in the slides.
vec4 vec_cross(vec4 a, vec4 b)
{
    vec4 crossd;
    float zero = 0.0;

    crossd.x = ((a.y * b.z) - 
                (a.z * b.y));
    crossd.y = ((a.z * b.x) -
                (a.x * b.z));
    crossd.z = ((a.x * b.y) -
                (a.y * b.x));
    crossd.w = zero;

    return crossd;
}

// this function uses the vec_print function to print out a matrix,
// going vector by vector.
void mat_print(mat4 a)
{
    printf("Matrix: \n");
    vec_print(a.x);
    vec_print(a.y);
    vec_print(a.z);
    vec_print(a.w);
}

// this function uses the vec_scale function to scale a matrix
// by a floating point value.
mat4 mat_scale(float scalar, mat4 a)
{
    mat4 scaled;
    scaled.x = vec_scale(scalar, a.x);
    scaled.y = vec_scale(scalar, a.y);
    scaled.z = vec_scale(scalar, a.z);
    scaled.w = vec_scale(scalar, a.w);
    return scaled;
}

// this function adds matrices by doing 4 operations of
// vector addition, one for each vector in each matrix.
mat4 mat_add(mat4 a, mat4 b)
{
    mat4 scaled;
    scaled.x = vec_add(a.x, b.x);
    scaled.y = vec_add(a.y, b.y);
    scaled.z = vec_add(a.z, b.z);
    scaled.w = vec_add(a.w, b.w);
    return scaled;
}

// this function subtracts matrices by doing 4 operations
// of vector subtraction, one on each vector in each matrix, then
// returining the resulting matrix.
mat4 mat_subtract(mat4 a, mat4 b)
{
    mat4 scaled;
    scaled.x = vec_subtract(a.x, b.x);
    scaled.y = vec_subtract(a.y, b.y);
    scaled.z = vec_subtract(a.z, b.z);
    scaled.w = vec_subtract(a.w, b.w);
    return scaled;
}

// this function multiplies a matrix by a matrix by
// transposing the second vector and then using
// vector multiplication to make the operation a little
// simpler, allowing us to multiply each vector by each
// vector in the transposed matrix.
mat4 mat_multiply(mat4 m1, mat4 m2) 
{
	mat4 result;
	result.x.x = (m1.x.x * m2.x.x) + (m1.y.x * m2.x.y) + (m1.z.x * m2.x.z) + (m1.w.x * m2.x.w);
	result.x.y = (m1.x.y * m2.x.x) + (m1.y.y * m2.x.y) + (m1.z.y * m2.x.z) + (m1.w.y * m2.x.w);
	result.x.z = (m1.x.z * m2.x.x) + (m1.y.z * m2.x.y) + (m1.z.z * m2.x.z) + (m1.w.z * m2.x.w);
	result.x.w = (m1.x.w * m2.x.x) + (m1.y.w * m2.x.y) + (m1.z.w * m2.x.z) + (m1.w.w * m2.x.w);
	result.y.x = (m1.x.x * m2.y.x) + (m1.y.x * m2.y.y) + (m1.z.x * m2.y.z) + (m1.w.x * m2.y.w);
	result.y.y = (m1.x.y * m2.y.x) + (m1.y.y * m2.y.y) + (m1.z.y * m2.y.z) + (m1.w.y * m2.y.w);
	result.y.z = (m1.x.z * m2.y.x) + (m1.y.z * m2.y.y) + (m1.z.z * m2.y.z) + (m1.w.z * m2.y.w);
	result.y.w = (m1.x.w * m2.y.x) + (m1.y.w * m2.y.y) + (m1.z.w * m2.y.z) + (m1.w.w * m2.y.w);
	result.z.x = (m1.x.x * m2.z.x) + (m1.y.x * m2.z.y) + (m1.z.x * m2.z.z) + (m1.w.x * m2.z.w);
	result.z.y = (m1.x.y * m2.z.x) + (m1.y.y * m2.z.y) + (m1.z.y * m2.z.z) + (m1.w.y * m2.z.w);
	result.z.z = (m1.x.z * m2.z.x) + (m1.y.z * m2.z.y) + (m1.z.z * m2.z.z) + (m1.w.z * m2.z.w);
	result.z.w = (m1.x.w * m2.z.x) + (m1.y.w * m2.z.y) + (m1.z.w * m2.z.z) + (m1.w.w * m2.z.w);
	result.w.x = (m1.x.x * m2.w.x) + (m1.y.x * m2.w.y) + (m1.z.x * m2.w.z) + (m1.w.x * m2.w.w);
	result.w.y = (m1.x.y * m2.w.x) + (m1.y.y * m2.w.y) + (m1.z.y * m2.w.z) + (m1.w.y * m2.w.w);
	result.w.z = (m1.x.z * m2.w.x) + (m1.y.z * m2.w.y) + (m1.z.z * m2.w.z) + (m1.w.z * m2.w.w);
	result.w.w = (m1.x.w * m2.w.x) + (m1.y.w * m2.w.y) + (m1.z.w * m2.w.z) + (m1.w.w * m2.w.w);
	return result;
}
// this function multiplies a matrix by a vector
// using the vector dot product function, which is essentially
// the same as what's going on in matrix multiplication
vec4 vec_mat_multiply(vec4 a, mat4 b)
{
    vec4 scaled;
	scaled.x = (b.x.x * a.x) + (b.y.x * a.y) + (b.z.x * a.z) + (b.w.x * a.w);
	scaled.y = (b.x.y * a.x) + (b.y.y * a.y) + (b.z.y * a.z) + (b.w.y * a.w);
	scaled.z = (b.x.z * a.x) + (b.y.z * a.y) + (b.z.z * a.z) + (b.w.z * a.w);
	scaled.w = (b.x.w * a.x) + (b.y.w * a.y) + (b.z.w * a.z) + (b.w.w * a.w);
	return scaled;
}

// this function is simple -- it reassigns the vectors
// into rows across each of 4 new vectors and returns
// a transposed matrix struct
mat4 mat_transpose(mat4 a)
{
    mat4 scaled;
    scaled.x = 
        (vec4){a.x.x, a.y.x, a.z.x, a.w.x};
    scaled.y = 
        (vec4){a.x.y, a.y.y, a.z.y, a.w.y};
    scaled.z = 
        (vec4){a.x.z, a.y.z, a.z.z, a.w.z};
    scaled.w = 
        (vec4){a.x.w, a.y.w, a.z.w, a.w.w};
    return scaled;
}

// this function checks if the matrix has an inversion
// by applying the first few steps of the mat_invert()
// function and checking if the determinant is 0.
// run before inverting matrix
int mat_invert_check(mat4 a)
{
    mat4 minor = mat_minor(a);
    float determinant = mat_determinant(a, minor);
    if (determinant == 0)
    {
        return 0;
    } 
    else
    {
        return 1;
    }
}

// using the many helper functions defined below, this
// function follows the format listed in the slides fairly
// closely to return an inverted matrix.
mat4 mat_invert(mat4 a)
{
    mat4 minor = mat_minor(a);
    float determinant = mat_determinant(a, minor);
    mat4 cofactor = mat_cofactor(minor);
    mat4 transpose = mat_transpose(cofactor);
    mat4 a_inv = mat_scale((1.0/determinant), transpose);
    return a_inv;
}

// this function manually goes through each position
// in the matrix a, creating a new matrix of minors
// to be used in the inverse matrix function.
// i've broken up each step of the process into
// more modular function blocks
mat4 mat_minor(mat4 a)
{
    mat4 scaled;

    scaled.x.x = mat3_determinant(mat_reduce(a, 1, 1));
    scaled.y.x = mat3_determinant(mat_reduce(a, 2, 1));
    scaled.z.x = mat3_determinant(mat_reduce(a, 3, 1));
    scaled.w.x = mat3_determinant(mat_reduce(a, 4, 1));
    scaled.x.y = mat3_determinant(mat_reduce(a, 1, 2));
    scaled.y.y = mat3_determinant(mat_reduce(a, 2, 2));
    scaled.z.y = mat3_determinant(mat_reduce(a, 3, 2));
    scaled.w.y = mat3_determinant(mat_reduce(a, 4, 2));
    scaled.x.z = mat3_determinant(mat_reduce(a, 1, 3));
    scaled.y.z = mat3_determinant(mat_reduce(a, 2, 3));
    scaled.z.z = mat3_determinant(mat_reduce(a, 3, 3));
    scaled.w.z = mat3_determinant(mat_reduce(a, 4, 3));
    scaled.x.w = mat3_determinant(mat_reduce(a, 1, 4));
    scaled.y.w = mat3_determinant(mat_reduce(a, 2, 4));
    scaled.z.w = mat3_determinant(mat_reduce(a, 3, 4));
    scaled.w.w = mat3_determinant(mat_reduce(a, 4, 4));

    return scaled;
}

// this function manually steps through every other position in the 4x4
// matrix and scales the float value stored within by -1.0, applying
// a checkerboard of minuses, as described in the slides.
mat4 mat_cofactor(mat4 minor)
{
    mat4 scaled;
    scaled = minor;
    scaled.x.y = (minor.x.y * -1.0);
    scaled.x.w = (minor.x.w * -1.0);
    scaled.y.x = (minor.y.x * -1.0);
    scaled.y.z = (minor.y.z * -1.0);
    scaled.z.y = (minor.z.y * -1.0);
    scaled.z.w = (minor.z.w * -1.0);
    scaled.w.x = (minor.w.x * -1.0);
    scaled.w.z = (minor.w.z * -1.0);
    return scaled;
}

// this function finds the determinant of a 4x4 matrix using
// the matrix of minors and the original matrix. it applies the
// formula found in the slides to do this
float mat_determinant(mat4 a, mat4 m)
{
    return ((a.x.x * m.x.x) -
            (a.x.y * m.x.y) +
            (a.x.z * m.x.z) -
            (a.x.w * m.x.w));
}

// imported translate function from template.c
// for use in transformation functions

/* this function takes in a matrix struct and reduces it into
 * a 3x3 mat3 object, which is constructed of 3 vec3 structs. */
mat3 mat_reduce(mat4 x, int col, int row)
{
    // first, we construct 3 new vectors
    vec4 a;
    vec4 b;
    vec4 c;

    // then, based on the column (entire vector) to be removed,
    // we assign the 3 remaining vectors to those new vectors
    switch (col)
    {
        case 1: // x
            a = x.y;
            b = x.z;
            c = x.w;
            break;
        case 2: // y
            a = x.x;
            b = x.z;
            c = x.w;
            break;
        case 3: // z
            a = x.x;
            b = x.y;
            c = x.w;
            break;
        default: // w
            a = x.x;
            b = x.y;
            c = x.z;
            break;    
    };

    // then we plug in the remaining vectors to the vec_reduce()
    // function, which operates similarly
    vec3 ax = vec_reduce(a, row);
    vec3 bx = vec_reduce(b, row);
    vec3 cx = vec_reduce(c, row);

    // finally, we construct the 3x3 mat3 struct with the reduced vectors
    mat3 scaled = {ax, bx, cx};

    // this mat3 object is sent to mat3_determinant()
    return scaled;
}

// this function operates in much the same way as the mat_reduce function,
// reducing the vectors to vec3 structs with every row but the specified one
// giving us a fully reduced 3x3 matrix to be used in matrix of minors
vec3 vec_reduce(vec4 a, int n)
{
    vec3 scaled;
    switch (n)
    {
        case 1:
            scaled = (vec3){a.y, a.z, a.w};
            break;
        case 2:
            scaled = (vec3){a.x, a.z, a.w};
            break;
        case 3:
            scaled = (vec3){a.x, a.y, a.w};
            break;
        default:
            scaled = (vec3){a.x, a.y, a.z};
            break;
    };
    return scaled;
}

/* using the rule of sarrus from the slides, this code takes the floats
 * stored in each vec3 struct positionally and plugs them into
 * that algorithm, returning the determinant for the matrix of minors. */
float mat3_determinant(mat3 a)
{
    return ((a.x.x * a.y.y * a.z.z) +
            (a.y.x * a.z.y * a.x.z) +
            (a.z.x * a.x.y * a.y.z) -
            (a.x.z * a.y.y * a.z.x) -
            (a.y.z * a.z.y * a.x.x) -
            (a.z.z * a.x.y * a.y.x));
}

mat4 translate(float x, float y, float z){
	mat4 result;

	result.x.x = 1; result.y.x = 0; result.z.x = 0; result.w.x = (float)x;
	result.x.y = 0; result.y.y = 1; result.z.y = 0; result.w.y = (float)y;
	result.x.z = 0; result.y.z = 0; result.z.z = 1; result.w.z = (float)z;
	result.x.w = 0; result.y.w = 0; result.z.w = 0; result.w.w = 1;

	return result;
}

mat4 scale(float x, float y, float z) 
{
    mat4 result = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    result.x.x = (float)x;
	result.y.y = (float)y;
	result.z.z = (float)z;
    
    return result;
}

// feed these into ctm
mat4 rotate_about_x(float theta)
{
    mat4 result = {{1,0,0,0},
            {0,cos(theta),sin(theta),0},
            {0,-(sin(theta)),cos(theta),0},
            {0,0,0,1}};
    
    return result;
}

mat4 rotate_about_z(float theta)
{
    mat4 result = {{cos(theta),sin(theta),0,0},
            {-(sin(theta)),cos(theta),0,0},
            {0,0,1,0},
            {0,0,0,1}};
    
    return result;
}

mat4 rotate_about_y(float theta)
{
    mat4 result = {{cos(theta),0,-(sin(theta)),0},
            {0,1,0,0},
            {sin(theta),0,cos(theta),0},
            {0,0,0,1}};

    return result;
}
mat4 look_at(vec4 eye, vec4 at, vec4 up)
{
	mat4 result;

	vec4 n = vec_subtract(eye, at);
	float magn = vec_magnitude(n);
	n = vec_scale(1 / magn, n);

    vec4 u = vec_cross(up, n);
    magn = vec_magnitude(u);
    u = vec_scale(1 / magn, u);

	vec4 v = vec_cross(n, u);
	magn = vec_magnitude(v);
	v = vec_scale(1 / magn, v);

	result.x.x = u.x;	
	result.x.y = v.x;	
	result.x.z = n.x;	
	result.x.w = eye.x;	
    result.y.x = u.y;
    result.y.y = v.y;
    result.y.z = n.y;
    result.y.w = eye.y;
    result.z.x = u.z;
    result.z.y = v.z;
    result.z.z = n.z;
    result.z.w = eye.z;
    result.w.x = 0;
    result.w.y = 0;
    result.w.z = 0;
    result.w.w = 1;

	result = mat_transpose(result);
	result = mat_invert(result);
	return result;
}
mat4 frustum(float left, float right, float bottom,
				float top, float near, float far)
{
	mat4 result;

	result.x.x = (-2 * near ) / (right - left);
	result.x.y = 0;						
	result.x.z = 0;						
	result.x.w = 0;						

    result.y.x = 0;						
    result.y.y = (-2 * near) / (top - bottom);
    result.y.z = 0;						
    result.y.w = 0;				

    result.z.x = (left + right) / (right - left);	
    result.z.y = (bottom + top) / (top - bottom);	
    result.z.z = (near + far) / (far - near);		
    result.z.w = -1;
    result.w.x = 0;
    result.w.y = 0;
    result.w.z = -1 * (2 * near * far) / (far - near);
    result.w.w = 0;					

	return result;
}

mat4 identity_matrix() {
    mat4 result;

	result.x.x = 1; result.y.x = 0; result.z.x = 0; result.w.x = 0;
	result.x.y = 0; result.y.y = 1; result.z.y = 0; result.w.y = 0;
	result.x.z = 0; result.y.z = 0; result.z.z = 1; result.w.z = 0;
	result.x.w = 0; result.y.w = 0; result.z.w = 0; result.w.w = 1;

	return result;
}