#include "model.hpp"

Model::Model() {
    num_verts = num_faces = num_edges = -1;
    verts = NULL;
    faces = NULL;
    edges = NULL;
    angle = 0;
}

Model::Model(const Model& other) {
    num_verts = other.num_verts;
    num_faces = other.num_faces;
    num_edges = other.num_edges;
    angle = other.angle;

    verts = new Vert[num_verts];
    faces = new Face[num_faces];
    edges = new Edge[num_edges];

    std::copy(other.verts, other.verts + num_verts, verts);
    std::copy(other.faces, other.faces + num_faces, faces);
    std::copy(other.edges, other.edges + num_edges, edges);
}

Model::~Model() {
    delete[] verts;
    delete[] faces;
    delete[] edges;
}

void Model::operator=(const Model& other) {
    delete[] verts;
    delete[] faces;
    delete[] edges;

    num_verts = other.num_verts;
    num_faces = other.num_faces;
    num_edges = other.num_edges;
    angle = other.angle;

    verts = new Vert[num_verts];
    faces = new Face[num_faces];
    edges = new Edge[num_edges];

    std::copy(other.verts, other.verts + num_verts, verts);
    std::copy(other.faces, other.faces + num_faces, faces);
    std::copy(other.edges, other.edges + num_edges, edges);
    
    // Translate the internal indexing into these arrays.
    for (unsigned int i = 0; i < num_verts; i++) {
        verts[i].edge = verts[i].edge - other.edges + edges;
    }
    for (unsigned int i = 0; i < num_faces; i++) {
        faces[i].edge = faces[i].edge - other.edges + edges;
    }
    for (unsigned int i = 0; i < num_edges; i++) {
        edges[i].vert = edges[i].vert - other.verts + verts;
        // Special case NULL == no face
        if (edges[i].face != NULL) {
            edges[i].face = edges[i].face - other.faces + faces;
        }
        edges[i].next = edges[i].next - other.edges + edges;
        edges[i].prev = edges[i].prev - other.edges + edges;
        edges[i].pair = edges[i].pair - other.edges + edges;
    }
}
