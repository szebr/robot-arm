/*
 * lab05.c
 *
 * A program that renders a cone and a cylinder
 */


#ifdef __APPLE__  // include Mac OS X verions of headers

#include <OpenGL/gl3.h>
#include <GLUT/glut.h>

#else // non-Mac OS X operating systems

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#endif  // __APPLE__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../mylib/initShader.h"
#include "../mylib/vec.h"

#define NUM_SIDES           36                              // NUMBER OF SIDES IN CYLINDER
#define CYL_TRIANGLES       NUM_SIDES * 4                   // NUMBER OF TRIANGLES IN A SINGLE CYLINDER
#define CYLINDER            3 * CYL_TRIANGLES               // NUMBER OF VERTICES IN A SINGLE CYLINDER
#define NUM_CYLINDERS       7                               // NUMBER OF CYLINDERS
#define VERTICES            NUM_CYLINDERS * CYLINDER        // TOTAL VERTICES
#define TRIANGLES           (VERTICES) / 3

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

mat4 currentRotation = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
int isRotating = 0;
int startX = 0, startY = 0;

GLuint ctm_location;
GLuint model_view_location;
GLuint projection_location;

mat4 ctm =                {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4 projection         = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4 model_view         = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
vec4 eye                = {10, 20, 0, 0};
vec4 at                 = {0, 0, 0, 0};
vec4 up                 = {0, 1, 0, 0};

vec4 vertices[VERTICES];
vec4 colors[VERTICES];

// mutable global values to control vertex indices
int vertices_index      = 0;                                // STARTING INDEX
int previous_index      = 0;                        // RETAIN PREVIOUS VERTEX INDEX

int at_cylinder = 0;

void update_index(int num) {
    previous_index = vertices_index;
    vertices_index = vertices_index + num;
}

void generate_cyl(vec4* cone) {
    int ix = vertices_index;
    for (int i = 0; i < NUM_SIDES; i++) {
        GLfloat angle1 = i * (2 * M_PI / NUM_SIDES);
        GLfloat angle2 = (i + 1) * (2 * M_PI / NUM_SIDES);

        // cyl base
        cone[ix + (i * 12    )].x = 0.0;
        cone[ix + (i * 12    )].y = -0.5;
        cone[ix + (i * 12    )].z = 0.0;
        cone[ix + (i * 12    )].w = 1.0;
        cone[ix + (i * 12 + 1)].x = 0.5 * sin(angle1);
        cone[ix + (i * 12 + 1)].y = -0.5;
        cone[ix + (i * 12 + 1)].z = 0.5 * cos(angle1);
        cone[ix + (i * 12 + 1)].w = 1.0;
        cone[ix + (i * 12 + 2)].x = 0.5 * sin(angle2);
        cone[ix + (i * 12 + 2)].y = -0.5;
        cone[ix + (i * 12 + 2)].z = 0.5 * cos(angle2);
        cone[ix + (i * 12 + 2)].w = 1.0;

        // cyl roof
        cone[ix + (i * 12 + 3)].x = 0.5 * sin(angle1);
        cone[ix + (i * 12 + 3)].y = 0.5;
        cone[ix + (i * 12 + 3)].z = 0.5 * cos(angle1);
        cone[ix + (i * 12 + 3)].w = 1.0;
        cone[ix + (i * 12 + 4)].x = 0.0;
        cone[ix + (i * 12 + 4)].y = 0.5;
        cone[ix + (i * 12 + 4)].z = 0.0;
        cone[ix + (i * 12 + 4)].w = 1.0;
        cone[ix + (i * 12 + 5)].x = 0.5 * sin(angle2);
        cone[ix + (i * 12 + 5)].y = 0.5;
        cone[ix + (i * 12 + 5)].z = 0.5 * cos(angle2);
        cone[ix + (i * 12 + 5)].w = 1.0;

        // cyl base wall
        cone[ix + (i * 12 + 6)].x = 0.5 * sin(angle1);
        cone[ix + (i * 12 + 6)].y = 0.5;
        cone[ix + (i * 12 + 6)].z = 0.5 * cos(angle1);
        cone[ix + (i * 12 + 6)].w = 1.0;
        cone[ix + (i * 12 + 7)].x = 0.5 * sin(angle2);
        cone[ix + (i * 12 + 7)].y = 0.5;
        cone[ix + (i * 12 + 7)].z = 0.5 * cos(angle2);
        cone[ix + (i * 12 + 7)].w = 1.0;
        cone[ix + (i * 12 + 8)].x = 0.5 * sin(angle2);
        cone[ix + (i * 12 + 8)].y = -0.5;
        cone[ix + (i * 12 + 8)].z = 0.5 * cos(angle2);
        cone[ix + (i * 12 + 8)].w = 1.0;

        // cyl roof wall
        cone[ix + (i * 12 + 9)].x = 0.5 * sin(angle2);
        cone[ix + (i * 12 + 9)].y = -0.5;
        cone[ix + (i * 12 + 9)].z = 0.5 * cos(angle2);
        cone[ix + (i * 12 + 9)].w = 1.0;
        cone[ix + (i * 12 +10)].x = 0.5 * sin(angle1);
        cone[ix + (i * 12 +10)].y = -0.5;
        cone[ix + (i * 12 +10)].z = 0.5 * cos(angle1);
        cone[ix + (i * 12 +10)].w = 1.0;
        cone[ix + (i * 12 +11)].x = 0.5 * sin(angle1);
        cone[ix + (i * 12 +11)].y = 0.5;
        cone[ix + (i * 12 +11)].z = 0.5 * cos(angle1);
        cone[ix + (i * 12 +11)].w = 1.0;
    }

    at_cylinder = at_cylinder + 1;
    update_index(CYLINDER);
}

void scale_cyl(vec4* vertices, float x, float y, float z) {
    int px = previous_index;
    printf("pillar: %d\n", (px));

    for(int i = 0; i < CYLINDER; i++){
    	vertices[i + px] = vec_mat_multiply(vertices[i + px], scale(x, y, z));
        if (i == 0) {
            printf("%f %f %f", vertices[i + px].x, vertices[i + px].y, vertices[i + px].z);
        }
    }
}
void move_cyl(vec4* vertices, float x, float y, float z) {
    int px = previous_index;
    for (int i = 0; i < CYLINDER; i++) {
        vertices[i + px] = vec_mat_multiply(vertices[i + px], translate(x, y, z));
        if (i == 0) {
            printf("%f %f %f", vertices[i + px].x, vertices[i + px].y, vertices[i + px].z);
        }
    }
}

void draw_cylinder(int num, mat4 transformer) {
    generate_cyl(vertices); // this updates the current_index (end of new shape) and previous index (start of new shape)
    int px = num * CYLINDER;
    for (int i = 0; i < CYLINDER; i++) {
        vertices[i + px] = vec_mat_multiply(vertices[i + px], transformer);
    }
}


// this function steps through each triangle and
// assigns it a random value between 0.0 and 1.0
// for the color vertices
void generate_colors(vec4* colors) {
    srand(time(NULL));

    for (int i = 0; i < TRIANGLES; i++) {
        GLfloat random = 0.2 * ((GLfloat)rand() / (GLfloat)RAND_MAX);
        GLfloat random2 = 0.5 * ((GLfloat)rand() / (GLfloat)RAND_MAX);
        GLfloat random3 = 0.8 * ((GLfloat)rand() / (GLfloat)RAND_MAX);
        colors[(i * 3)].x = random;
        colors[(i * 3)].y = random2;
        colors[(i * 3)].z = random3;
        colors[(i * 3)].w = 1.0;
        colors[(i * 3) + 1].x = random;
        colors[(i * 3) + 1].y = random2;
        colors[(i * 3) + 1].z = random3;
        colors[(i * 3) + 1].w = 1.0;
        colors[(i * 3) + 2].x = random;
        colors[(i * 3) + 2].y = random2;
        colors[(i * 3) + 2].z = random3;
        colors[(i * 3) + 2].w = 1.0;
    }
}


void init(void)
{
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices));

	ctm_location = glGetUniformLocation(program, "ctm");
    model_view_location = glGetUniformLocation(program, "model_view");
    projection_location = glGetUniformLocation(program, "projection");

	printf("ctm_location:%i\n", ctm_location);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void generate_cylinders() {

        generate_cyl(vertices);
        scale_cyl(vertices, 3.5, 5, 3.5);
        move_cyl(vertices, 0, 2.5, 0);

        generate_cyl(vertices);
        scale_cyl(vertices, 3.5, 5, 3.5);
        move_cyl(vertices, 0, 2.5, 0);
        scale_cyl(vertices, 0.9, 0.9, 0.9);

        generate_cyl(vertices);
        scale_cyl(vertices, 3.5, 5, 3.5);
        move_cyl(vertices, 0, 2.5, 0);
        scale_cyl(vertices, 0.75, 0.75, 0.75);

        generate_cyl(vertices);
        scale_cyl(vertices, 3.5, 5, 3.5);
        move_cyl(vertices, 0, 2.5, 0);
        scale_cyl(vertices, 0.6, 0.6, 0.6);

        // FINGERS
        generate_cyl(vertices);
        scale_cyl(vertices, .75, 10, .75);
        move_cyl(vertices, 0, 5, 0);
        scale_cyl(vertices, 0.3, 0.3, 0.3);

        generate_cyl(vertices);
        scale_cyl(vertices, .75, 10, .75);
        move_cyl(vertices, 0, 5, 0);
        scale_cyl(vertices, 0.3, 0.3, 0.3);

        // BASE
        generate_cyl(vertices);
        scale_cyl(vertices, 40, .5, 40);
        move_cyl(vertices, 0, -.25, 0);
    
    generate_colors(colors);
}

float rotate_base = 0;
float rotate_lower = 0;
float rotate_mid = 0;
float rotate_upper = 0;
float pinch = 1;
float fu = 0;
float fd = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    projection = frustum(-1 + fd, 1 + fu, -1 + fd, 1 + fu, -1, -150);


    mat4 base = rotate_about_y(rotate_base);
    
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &base);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glDrawArrays(GL_TRIANGLES, 0, CYLINDER);
        // =======================
        mat4 l_rotate = rotate_about_z(rotate_lower);
        mat4 l_translate = translate(0,5,0);

        mat4 lower = mat_multiply(l_translate, l_rotate);
        mat4 lower_ctm = mat_multiply(base, lower);

        glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &lower_ctm);
        glDrawArrays(GL_TRIANGLES, CYLINDER, CYLINDER);
        // =======================
        mat4 m_rotate = rotate_about_z(rotate_mid);
        mat4 m_translate  = translate(0,4.5,0);

        mat4 mid = mat_multiply(m_translate, m_rotate);
        mat4 mid_ctm = mat_multiply(lower_ctm, mid);

        glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &mid_ctm);
        glDrawArrays(GL_TRIANGLES, (CYLINDER) *2, CYLINDER);
        // =======================
        mat4 u_rotate = rotate_about_y(rotate_upper);
        mat4 u_translate = translate(0,3.75,0);

        mat4 upper = mat_multiply(u_translate, u_rotate);
        mat4 upper_ctm = mat_multiply(mid_ctm, upper);


        glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &upper_ctm);
        glDrawArrays(GL_TRIANGLES, (CYLINDER) *3, CYLINDER);
        //* =======================
        mat4 f1_translate = translate(0,3,-0.8*pinch);
        mat4 finger_1 = mat_multiply(f1_translate, ctm);
        mat4 finger_1_ctm = mat_multiply(upper_ctm, finger_1);

        glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &finger_1_ctm);
        glDrawArrays(GL_TRIANGLES, (CYLINDER) *4, CYLINDER);
        //* =======================
        mat4 f2_translate = translate(0,3,.8*pinch);
        mat4 finger_2 = mat_multiply(f2_translate, ctm);
        mat4 finger_2_ctm = mat_multiply(upper_ctm, finger_2);

        glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &finger_2_ctm);
        glDrawArrays(GL_TRIANGLES, (CYLINDER) *5, CYLINDER);
        
        glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
        glDrawArrays(GL_TRIANGLES, (CYLINDER) *6, CYLINDER);

    glutSwapBuffers();
}

void motion(int x, int y) {
    if (isRotating == 1) {
        // change in pos
        int deltaX = x - startX;
        int deltaY = y - startY;

        startX = x;
        startY = y;

        GLfloat theta = 0.01 * deltaY;
        GLfloat phi = 0.01 * deltaX;

        mat4 rotationX = rotate_about_x(theta);
        mat4 rotationY = rotate_about_y(phi);

        currentRotation = mat_multiply(rotationY, rotationX);

        ctm = mat_multiply(ctm, currentRotation);

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) { // left button press
            isRotating = 1;
            startX = x;
            startY = y;
        } else if (state == GLUT_UP) { // left button released
            isRotating = 0;
        }
    }
    glutPostRedisplay();
}

int speed = 3;

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
        exit(0);
    if(key == 'u') { //up
        int up = eye.y;
        eye.y = up + 1;
    }
    if(key == 'n') { //left
        eye = vec_mat_multiply(eye, rotate_about_y(0.0349 * speed));
    }
    if(key == 'e') { //down
        int down = eye.y;
        eye.y = down - 1;
    }
    if(key == 'i') { //right
        eye = vec_mat_multiply(eye, rotate_about_y(-0.0349 * speed));
    }
    if(key == 'l') { //forward
        int forward = eye.x;
        eye.x = forward - 1;
    }
    if(key == 'y') { //back
        int back = eye.x;
        eye.x = back + 1;
    }
    if(key == '1') { //rotate base left
        rotate_base = rotate_base + 0.0349;
    }
    if(key == '2') { //rotate base left
        rotate_base = rotate_base - 0.0349;
    }
    if(key == '3') { //rotate base left
        rotate_lower = rotate_lower + 0.0349;
    }
    if(key == '4') { //rotate base left
        rotate_lower = rotate_lower - 0.0349;
    }
    if(key == '5') { //rotate base left
        rotate_mid = rotate_mid + 0.0349;
    }
    if(key == '6') { //rotate base left
        rotate_mid = rotate_mid - 0.0349;
    }
    if(key == '7') { //rotate base left
        rotate_upper = rotate_upper + 0.0349;
    }
    if(key == '8') { //rotate base left
        rotate_upper = rotate_upper - 0.0349;
    }
    if(key == '9') { //rotate base left
        if (pinch > 0.2) {
            pinch = pinch - 0.1;
        }
    }
    if(key == '0') { //rotate base left
        if (pinch < 1.0) {
            pinch = pinch + 0.1;
        }

    }
    if(key == 'a') { //rotate base left
        fd = fd - 0.08;
        fu = fu + 0.08;
    }
    if(key == 'r') { //rotate base left
        fd = fd + 0.08;
        fu = fu - 0.08;

    }

    glutPostRedisplay();
}

void idle(void)
{
    model_view = look_at(eye, at, up);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    generate_cylinders();

    model_view = look_at(eye, at, up);
    projection = frustum(-1, 1, -1, 1, -1, -150);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Triangle");
    //glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
