#include "view.hpp"

#include <glew.h>
#include <GL/glut.h>

#include "common.hpp"
#include "player.hpp"
#include "shaders.hpp"
#include "lights.hpp"

double fov    = 50.0,
       near   = 0.1,
       far    = 100.0,
       aspect = 0.0;

int height = 0,
    width = 0;

void view_init(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Assignment 2, Wim Looman");

    glewInit();
    shaders_init();
    lights_init();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void view_reshape(int new_width, int new_height) {
    glViewport(0, 0, new_width, new_height);
    width = new_width;
    height = new_height;
    aspect = new_width / (double)new_height;
}

void view_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    player_look();

    lights_display();

    glPolygonMode(GL_FRONT, GL_FILL);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glColor4f(0.58, 0.27, 0.20, 1.0);
    model.display();

    glPolygonMode(GL_BACK, GL_LINE);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_FRONT);
    glColor4f(0.0, 0.0, 0.0, 1.0);
    model.display();

    glutSwapBuffers();
}
