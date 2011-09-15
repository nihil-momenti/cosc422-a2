#include "model.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <set>

std::set<Model*> rotating_models;

void rotate_models(int value) {
    for (std::set<Model*>::iterator it = rotating_models.begin(); it != rotating_models.end(); it++) {
        (*it)->angle = ((*it)->angle + 1) % 360;
    }
}

void queue_rotation(Model *model) {
    rotating_models.insert(model);
}

void deque_rotation(Model *model) {
    rotating_models.erase(model);
}

void Model::display() {
    glPushMatrix();
    //glRotated((GLdouble)angle, 0, 1, 0);

    glBegin(GL_TRIANGLES);

    for (unsigned int i = 0; i < num_faces; i++) {
        faces[i].display();
    }

    glEnd();

    glPopMatrix();
}
