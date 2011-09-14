#include "halfedge.hpp"

Edge::Edge() {
    vert = NULL;
    face = NULL;
    next = NULL;
    prev = NULL;
    pair = NULL;
}
