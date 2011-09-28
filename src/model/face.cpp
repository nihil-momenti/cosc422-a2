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

//void Face::display() {
//    Edge *e = edge;
//
//    do {
//        Point  point =  e->vert->point;
//        Vector normal = e->vert->normal();
//        Vector dir = e->vert->point - edge->vert->point;
//
//        glMultiTexCoord2d(GL_TEXTURE0, 0.5, 0.5);
//        glMultiTexCoord2d(GL_TEXTURE1, 0.5, 0.5);
//        glMultiTexCoord2d(GL_TEXTURE2, 0.5, 0.5);
//
//        glNormal3d(normal.dx, normal.dy, normal.dz);
//        glVertex3d(point.x, point.y, point.z);
//
//        e = e->next;
//    } while (e != edge);
//}

void Face::display() {
    Vert *v1 = edge->vert,
         *v2 = edge->next->vert,
         *v3 = edge->prev->vert;

    glMultiTexCoord2d(GL_TEXTURE0, 0.5, 0.5);
    glMultiTexCoord2d(GL_TEXTURE1, 0.5, 0.5);
    glMultiTexCoord2d(GL_TEXTURE2, 0.5, 0.5);

    glNormal3d(v1->normal().dx, v1->normal().dy, v1->normal().dz);
    glVertex3d(v1->point.x, v1->point.y, v1->point.z);

    glMultiTexCoord2d(GL_TEXTURE0, 0.5 + 0.5 * (v2->point - v1->point).unit().dx, 0.5 + 0.5 * (v2->point - v1->point).unit().dy);
    glMultiTexCoord2d(GL_TEXTURE1, 0.5 + 0.5 * (v2->point - v1->point).unit().dx, 0.5 + 0.5 * (v2->point - v1->point).unit().dy);
    glMultiTexCoord2d(GL_TEXTURE2, 0.5 + 0.5 * (v2->point - v1->point).unit().dx, 0.5 + 0.5 * (v2->point - v1->point).unit().dy);

    glNormal3d(v2->normal().dx, v2->normal().dy, v2->normal().dz);
    glVertex3d(v2->point.x, v2->point.y, v2->point.z);

    glMultiTexCoord2d(GL_TEXTURE0, 0.5 + 0.5 * (v3->point - v1->point).unit().dx, 0.5 + 0.5 * (v3->point - v1->point).unit().dy);
    glMultiTexCoord2d(GL_TEXTURE1, 0.5 + 0.5 * (v3->point - v1->point).unit().dx, 0.5 + 0.5 * (v3->point - v1->point).unit().dy);
    glMultiTexCoord2d(GL_TEXTURE2, 0.5 + 0.5 * (v3->point - v1->point).unit().dx, 0.5 + 0.5 * (v3->point - v1->point).unit().dy);

    glNormal3d(v3->normal().dx, v3->normal().dy, v3->normal().dz);
    glVertex3d(v3->point.x, v3->point.y, v3->point.z);
}
