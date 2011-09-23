#include <GL/glut.h>

#include "halfedge.hpp"

Face::Face() {
    edge   = NULL;
    mem_normal = Vector();
}

Vector Face::normal() {
    if (mem_normal != Vector()) {
        return mem_normal;
    }

    Point point1 = edge->vert->point,
          point2 = edge->next->vert->point,
          point3 = edge->prev->vert->point;

    mem_normal = (point2 - point1).cross(point3 - point1).unit();
    return mem_normal;
}

void Face::display() {
    Edge *e = edge;

    do {
        Point  point =  e->vert->point;
        Vector normal = e->vert->normal();
        Vector dir = e->vert->point - edge->vert->point;

        glNormal3d(normal.dx, normal.dy, normal.dz);
        glTexCoord3d(0.5+10*dir.dx, 0.5+10*dir.dy, 0.0);
        glVertex3d(point.x, point.y, point.z);

        e = e->next;
    } while (e != edge);
}
