#ifndef MODEL_HPP
#define MODEL_HPP
#include <string>
#include <vector>

#include "../geom.hpp"
#include "halfedge.hpp"

class Model {
    public:
        Model();
        Model(const Model&);
        Model(const std::string);

        ~Model();

        void operator=(const Model&);

        void display();
        void collapse_some_edge();
        void collapse_some_edges();
        void toggle_error_metric();
        unsigned int current_faces();
        void calculate_normals();
        void toggle_normal_map_display();

    private:
        Vert *verts;
        Face *faces;
        Edge *edges;

        unsigned int num_verts, num_faces, num_edges;
};
#endif
