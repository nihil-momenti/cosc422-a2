#include "lights.hpp"

#include <GL/gl.h>

void lights_init() {
    glEnable(GL_LIGHTING);

    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;

    float params[4] = {0.0, 0.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, params);

    params[0] = params[1] = params[2] = 1.0;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, params);
    glLightfv(GL_LIGHT0, GL_SPECULAR, params);

    params[0] = params[1] = 0.0;
    params[2] = 2.0;

    glLightfv(GL_LIGHT0, GL_POSITION, params);

    glEnable(GL_LIGHT0);

    GLfloat params1[4] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, params1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, params1);
}
