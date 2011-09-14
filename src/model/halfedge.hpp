#ifndef HALFEDGE_HPP
#define HALFEDGE_HPP

#include <set>

#include "../geom.hpp"

class Vert;
class Edge;
class Face;

typedef std::set<Vert*> VertSet;
typedef VertSet::iterator VertSet_IT;

class Edge {
    public:
        Edge();

        Vert *vert;
        Face *face;
        Edge *next;
        Edge *prev;
        Edge *pair;
};

class Vert {
    public:
        Vert();

        Vector normal();
        VertSet one_ring();
        VertSet two_ring();

        Point point;
        Edge *edge;

    private:
        Vector mem_normal;
};

class Face {
    public:
        Face();
        Vector normal();
        void display();

        Edge *edge;

    private:
        Vector mem_normal;
};

VertSet intersection(const VertSet &set1, const VertSet &set2);

#endif /* HALFEDGE_HPP */
