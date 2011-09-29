#include "halfedge.hpp"

#include <math.h>
#include <stdlib.h>

Vert::Vert() {
    point = Point();
    mem_normal = Vector();
    edge = NULL;
}

Vector Vert::normal() {
    if (mem_normal == Vector()) {
        Edge *e = edge;

        do {
            if (e->face != NULL) {
                mem_normal = mem_normal + (e->face->normal() * e->face->area());
            }
            e = e->pair->prev;
        } while (e != edge);

        mem_normal = mem_normal.unit();
    }

    return mem_normal;
}

static double sign(double num) {
    if (num < 0.0) {
        return -1.0;
    } else {
        return 1.0;
    }
}

Vector Vert::max_curvature_dir() {
    if (mem_max_curvature_dir == Vector()) {
        calc_curvature();
    }

    return mem_max_curvature_dir;
}

void Vert::calc_curvature() {
    Edge *e = edge;

    Matrix3 m = Matrix3();
    double wij_sum = 0.0;
    do {
        Vector tij = ((Matrix3::identity() - Matrix3(normal(), normal())) * e->pair->vect()).unit();
        double kij = 2 * normal().dot(e->pair->vect()) / pow(e->pair->vect().length(),2);
        double wij = 0.0;
        if (e->face != NULL)       { wij += e->face->area(); }
        if (e->pair->face != NULL) { wij += e->pair->face->area(); }
        wij_sum += wij;
        m = m + wij * kij * Matrix3(tij, tij);

        e = e->pair->prev;
    } while (e != edge);

    m = m / wij_sum;

    Vector e1 = Vector(1, 0, 0);
    Vector wvi;
    if ((e1 - normal()).length() > (e1 + normal()).length()) {
        wvi = (e1 - normal()).unit();
    } else {
        wvi = (e1 + normal()).unit();
    }

    Matrix3 qvi = Matrix3::identity() - 2 * Matrix3(wvi,wvi);

    Matrix3 m2 = qvi.transpose() * m * qvi;

    double m11   = m2.values[4],
           m12   = m2.values[7],
           m22   = m2.values[8],
           beta  = (m22 - m11) / 2 / m12,
           t     = sign(beta) / (abs(beta) + sqrt(pow(beta, 2) + 1)),
           c     = 1.0 / sqrt(pow(t,2) + 1),
           s     = c * t,
           m11_p = pow(c,2) * m11 + pow(s,2) * m22 - 2 * c * s * m12,
           m22_p = pow(s,2) * m11 + pow(c,2) * m22 + 2 * c * s * m12,
           phi   = atan(t),
           k1_p  = 3 * m11_p - m22_p,
           k2_p  = 3 * m22_p - m11_p;

    if (k1_p < k2_p) {
        mem_max_curvature_mag = k1_p;
        mem_max_curvature_dir = cos(phi) * qvi.col(1) - sin(phi) * qvi.col(2);
        mem_min_curvature_mag = k2_p;
        mem_min_curvature_dir = sin(phi) * qvi.col(1) + cos(phi) * qvi.col(2);
    } else {
        mem_max_curvature_mag = k2_p;
        mem_max_curvature_dir = sin(phi) * qvi.col(1) + cos(phi) * qvi.col(2);
        mem_min_curvature_mag = k1_p;
        mem_min_curvature_dir = cos(phi) * qvi.col(1) - sin(phi) * qvi.col(2);
    }
}

VertSet Vert::one_ring() {
    VertSet result = VertSet();

    Edge *e = edge;
    do {
        result.insert(e->pair->vert);
        e = e->pair->prev;
    } while(e != edge);

    return result;
}

VertSet Vert::two_ring() {
    VertSet result = VertSet();

    VertSet first_ring = edge->vert->one_ring();

    for (VertSet_IT it = first_ring.begin(); it != first_ring.end(); it++) {
        VertSet temp_ring = (*it)->edge->vert->one_ring();
        for (VertSet_IT it = temp_ring.begin(); it != temp_ring.end(); it++) {
            result.insert(*it);
        }
    }

    return result;
}

VertSet intersection(const VertSet &set1, const VertSet &set2) {
    VertSet result = VertSet();
    for (VertSet_const_IT it = set1.begin(); it != set1.end(); it++) {
        if (set2.find(*it) != set2.end()) {
            result.insert(*it);
        }
    }
    return result;
}
