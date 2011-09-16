#include "lights.hpp"

#include <GL/gl.h>

void lights_init() {
    GLfloat ambient[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[4] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse);

    GLfloat emission[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 60);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void lights_display() {
    GLfloat position[4] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}
