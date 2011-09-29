#include <glew.h>
#include <GL/glut.h>

#include "halfedge.hpp"

static const double SCALE = 10.0;

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
    Vert *v1 = edge->vert,
         *v2 = edge->next->vert,
         *v3 = edge->prev->vert;

    Vector tangent_1_2 = ((v2->point - v1->point) - (v2->point - v1->point).dot(v1->normal()) * v1->normal());
    Vector tangent_1_3 = ((v3->point - v1->point) - (v3->point - v1->point).dot(v1->normal()) * v1->normal());
    Vector tangent_2_1 = ((v1->point - v2->point) - (v1->point - v2->point).dot(v2->normal()) * v2->normal());
    Vector tangent_2_3 = ((v3->point - v2->point) - (v3->point - v2->point).dot(v2->normal()) * v2->normal());
    Vector tangent_3_1 = ((v1->point - v3->point) - (v1->point - v3->point).dot(v3->normal()) * v3->normal());
    Vector tangent_3_2 = ((v2->point - v3->point) - (v2->point - v3->point).dot(v3->normal()) * v3->normal());

    double dist_1_2_x = tangent_1_2.dot(v1->max_curvature_dir().unit()),
           dist_1_2_y = tangent_1_2.dot(v1->max_curvature_dir().cross(v1->normal()).unit()),
           dist_1_3_x = tangent_1_3.dot(v1->max_curvature_dir().unit()),
           dist_1_3_y = tangent_1_3.dot(v1->max_curvature_dir().cross(v1->normal()).unit());

    double dist_2_1_x = tangent_2_1.dot(v2->max_curvature_dir().unit()),
           dist_2_1_y = tangent_2_1.dot(v2->max_curvature_dir().cross(v2->normal()).unit()),
           dist_2_3_x = tangent_2_3.dot(v2->max_curvature_dir().unit()),
           dist_2_3_y = tangent_2_3.dot(v2->max_curvature_dir().cross(v2->normal()).unit());

    double dist_3_1_x = tangent_3_1.dot(v3->max_curvature_dir().unit()),
           dist_3_1_y = tangent_3_1.dot(v3->max_curvature_dir().cross(v3->normal()).unit()),
           dist_3_2_x = tangent_3_2.dot(v3->max_curvature_dir().unit()),
           dist_3_2_y = tangent_3_2.dot(v3->max_curvature_dir().cross(v3->normal()).unit());

    glMultiTexCoord2d(GL_TEXTURE0, 0.0, 0.0);
    glMultiTexCoord2d(GL_TEXTURE1, SCALE * dist_2_1_x, SCALE * dist_2_1_y);
    glMultiTexCoord2d(GL_TEXTURE2, SCALE * dist_3_1_x, SCALE * dist_3_1_y);

    glNormal3d(v1->normal().dx, v1->normal().dy, v1->normal().dz);
    glVertex3d(v1->point.x, v1->point.y, v1->point.z);

    glMultiTexCoord2d(GL_TEXTURE0, SCALE * dist_1_2_x, SCALE * dist_1_2_y);
    glMultiTexCoord2d(GL_TEXTURE1, 0.0, 0.0);
    glMultiTexCoord2d(GL_TEXTURE2, SCALE * dist_3_2_x, SCALE * dist_3_2_y);

    glNormal3d(v2->normal().dx, v2->normal().dy, v2->normal().dz);
    glVertex3d(v2->point.x, v2->point.y, v2->point.z);

    glMultiTexCoord2d(GL_TEXTURE0, SCALE * dist_1_3_x, SCALE * dist_1_3_y);
    glMultiTexCoord2d(GL_TEXTURE1, SCALE * dist_2_3_x, SCALE * dist_2_3_y);
    glMultiTexCoord2d(GL_TEXTURE2, 0.0, 0.0);

    glNormal3d(v3->normal().dx, v3->normal().dy, v3->normal().dz);
    glVertex3d(v3->point.x, v3->point.y, v3->point.z);
}
