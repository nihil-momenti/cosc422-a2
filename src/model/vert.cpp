#include "halfedge.hpp"

Vert::Vert() {
    point = Point();
    mem_normal = Vector();
    edge = NULL;
}

Vector Vert::normal() {
    if (mem_normal == Vector()) {
        Edge *e = edge;

        do {
            mem_normal = mem_normal + e->face->normal();
            e = e->pair->prev;
        } while (e != edge);

        mem_normal = mem_normal.unit();
    }

    return mem_normal;
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
    for (VertSet_IT it = set1.begin(); it != set1.end(); it++) {
        if (set2.find(*it) != set2.end()) {
            result.insert(*it);
        }
    }
    return result;
}
