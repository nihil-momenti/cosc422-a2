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
        void start_rotation();
        void stop_rotation();
        void toggle_rotation();
        void collapse_some_edge();
        void collapse_some_edges();
        void toggle_error_metric();
        unsigned int current_faces();
        void calculate_normals();
        void toggle_normal_map_display();
        void gl_init();

    private:
        Vert *verts;
        Face *faces;
        Edge *edges;

        int angle;
        friend void rotate_models(int value);

        unsigned int num_verts, num_faces, num_edges;
        unsigned int display_list;
};
#endif
