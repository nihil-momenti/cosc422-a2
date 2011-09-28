#ifndef HALFEDGE_HPP
#define HALFEDGE_HPP

#include <set>

#include "../geom.hpp"

class Vert;
class Edge;
class Face;

typedef std::set<Vert*> VertSet;
typedef VertSet::iterator VertSet_IT;
typedef VertSet::const_iterator VertSet_const_IT;

class Edge {
    public:
        Edge();

        Vector vect();

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
        void calc_curvature();
        Vector mem_normal;
        Vector max_curvature_dir,
               min_curvature_dir;
        double max_curvature_mag,
               min_curvature_mag;
};

class Face {
    public:
        Face();
        Vector normal();
        double area();
        void display();

        Edge *edge;

    private:
        Vector mem_normal;
        double mem_area;
        void calculate_normal();
};

VertSet intersection(const VertSet &set1, const VertSet &set2);

#endif /* HALFEDGE_HPP */
