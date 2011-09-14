#ifndef VERT_HPP
#define VERT_HPP

#include "geom.hpp"

struct HE_edge;

struct HE_vert {
    Point point;
    HE_edge *edge;
    Vector normal;
};

#endif /* VERT_HPP */
