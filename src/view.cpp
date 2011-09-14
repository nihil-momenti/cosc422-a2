#include "view.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "common.hpp"
#include "player.hpp"
#include "model.hpp"

double fov    = 50.0,
       near   = 0.1,
       far    = 100.0,
       aspect = 0.0;

int height = 0,
    width = 0;

void view_init(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Assignment 2, Wim Looman");

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutIgnoreKeyRepeat(1);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;
    float params[4] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, params);
    params[0] = params[1] = params[2] = 1.0;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, params);
    glLightfv(GL_LIGHT0, GL_SPECULAR, params);
    glEnable(GL_LIGHT0);
    GLfloat params1[4];
    params1[0] = params1[1] = params1[2] = 0.0;
    params1[4] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, params1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, params1);
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
    //gluLookAt(0.,0.,3.,0.,0.,0.,0.,1.,0.);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(0.8,0.0,0.0);
    model.display();

    glFlush();
    glutSwapBuffers();
}
