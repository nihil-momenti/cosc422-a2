#include "model.hpp"

#include <GL/glut.h>

#include <set>

#include "../texture.hpp"

std::set<Model*> rotating_models;
bool rotating = false;

void rotate_models(int value) {
    for (std::set<Model*>::iterator it = rotating_models.begin(); it != rotating_models.end(); it++) {
        (*it)->angle = ((*it)->angle + 1) % 360;
    }
    if (rotating) {
        glutTimerFunc(10, rotate_models, 0);
    }
    glutPostRedisplay();
}

void Model::start_rotation() {
    rotating_models.insert(this);
    if (! rotating) {
        rotating = true;
        glutTimerFunc(10, rotate_models, 0);
    }
}

void Model::stop_rotation() {
    rotating_models.erase(this);
    if (rotating_models.size() == 0) {
        rotating = false;
    }
}

void Model::toggle_rotation() {
    if (rotating_models.find(this) == rotating_models.end()) {
        start_rotation();
    } else {
        stop_rotation();
    }
}

void Model::gl_init() {
    display_list = glGenLists(1);

    glNewList(display_list, GL_COMPILE);
    glBindTexture(GL_TEXTURE_3D, tex_id);
    glBegin(GL_TRIANGLES);

    for (unsigned int i = 0; i < num_faces; i++) {
        faces[i].display();
    }

    glEnd();
    glEndList();
}

void Model::display() {
    glPushMatrix();
    glRotated(angle, 0.0, 1.0, 0.0);

    glCallList(display_list);

    glPopMatrix();
}
