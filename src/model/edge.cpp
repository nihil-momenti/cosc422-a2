#include "halfedge.hpp"

Edge::Edge() {
    vert = NULL;
    face = NULL;
    next = NULL;
    prev = NULL;
    pair = NULL;
}

Vector Edge::vect() {
    return pair->vert->point - vert->point;
}
