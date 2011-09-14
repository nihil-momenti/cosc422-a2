#include "model.hpp"

#include <GL/gl.h>

void Model::display() {
    glBegin(GL_TRIANGLES);

    for (unsigned int i = 0; i < num_faces; i++) {
        faces[i].display();
    }

    glEnd();
}
