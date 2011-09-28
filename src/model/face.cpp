#include <GL/glut.h>

#include "halfedge.hpp"

Face::Face() {
    edge   = NULL;
    mem_normal = Vector();
    mem_area = 0.0;
}

void Face::calculate_normal() {
    Point point1 = edge->vert->point,
          point2 = edge->next->vert->point,
          point3 = edge->prev->vert->point;

    Vector normal = (point2 - point1).cross(point3 - point1);
    mem_normal = normal.unit();
    mem_area = normal.length();
}

Vector Face::normal() {
    if (mem_normal == Vector()) {
        calculate_normal();
    }

    return mem_normal;
}

double Face::area() {
    if (mem_area == 0.0) {
        calculate_normal();
    }

    return mem_area;
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
