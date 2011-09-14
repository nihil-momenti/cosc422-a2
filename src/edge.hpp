#ifndef EDGE_HPP
#define EDGE_HPP

class Face;
struct HE_vert;

struct HE_edge {
    HE_vert *vert;
    Face *face;
    HE_edge *next;
    HE_edge *prev;
    HE_edge *pair;
};

#include "vert.hpp"
#include "face.hpp"

#endif /* EDGE_HPP */
