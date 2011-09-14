#ifndef FACE_HPP
#define FACE_HPP

#include "geom.hpp"
#include "edge.hpp"

class Face {
    public:
        Face();
        Vector normal();
        void display();

        HE_edge *edge;

    private:
        Vector mem_normal;
};

#endif /* FACE_HPP */
