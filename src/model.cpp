#include <algorithm>
#include <set>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <float.h>

#include "model.hpp"

Model::Model() {
    num_verts = num_faces = num_edges = -1;
    verts = NULL;
    faces = NULL;
    edges = NULL;
}

Model::Model(const Model& other) {
    num_verts = other.num_verts;
    num_faces = other.num_faces;
    num_edges = other.num_edges;

    verts = new HE_vert[num_verts];
    faces = new Face[num_faces];
    edges = new HE_edge[num_edges];

    std::copy(other.verts, other.verts + num_verts, verts);
    std::copy(other.faces, other.faces + num_faces, faces);
    std::copy(other.edges, other.edges + num_edges, edges);
}

Model::Model(const std::string filename) {
    std::ifstream fp_in;
    float vx,vy,vz;

    fp_in.open(filename.c_str());
    if(fp_in.fail()) {
        std::cout << "Error opening mesh file" << std::endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');                //ignore first line
    fp_in >> num_verts >> num_faces >> num_edges;

    verts = new HE_vert[num_verts];

    for (unsigned int i = 0; i < num_verts; i++) {
        fp_in >> vx >> vy >> vz;
        verts[i].point = Point(vx,vy,vz);
        verts[i].edge = NULL;
    }

    num_edges = num_faces * 3;
    
    faces = new Face[num_faces];
    // Need extra space for boundary edges.  Requirements unknown but at most the same as the number of edges.
    edges = new HE_edge[2*num_edges];

    unsigned int num, k[3], l;
    for (unsigned int i = 0; i < num_faces; i++) {
        fp_in >> num >> k[0] >> k[1] >> k[2];

        if (num != 3) {
            std::cout << "ERROR: Polygon with index " << i  << " is not a triangle." << std::endl;  //Not a triangle!!
            exit(1);
        }

        for (unsigned int j = 0; j < 3; j++) {
            edges[3*i+j].vert = &verts[k[j]];
            verts[k[j]].edge = &edges[3*i+j];
            edges[3*i+j].next = &edges[3*i+(j+1)%3];
            edges[3*i+j].prev = &edges[3*i+(j+2)%3];
            edges[3*i+j].face = &faces[i];
            edges[3*i+j].pair = NULL;
        }

        faces[i].edge = &edges[3*i];

        l = 3*(i+1);
    }
    
    fp_in.close();

    std::cout << " File successfully read." << std::endl;

    for (unsigned int i = 0; i < num_edges; i++) {
        if (edges[i].pair == NULL) {
            for (unsigned int j = i+1; j < num_edges; j++) {
                if (edges[j].vert == edges[i].prev->vert && edges[j].prev->vert == edges[i].vert) {
                    edges[i].pair = &edges[j];
                    edges[j].pair = &edges[i];
                    break;
                }
            }
            // No edge found so create a boundary edge.
            if (edges[i].pair == NULL) {
                edges[i].pair = &edges[l];

                edges[l].vert = edges[i].prev->vert;

                HE_edge *e1 = &edges[i];
                do {
                    e1 = e1->prev->pair;
                } while(e1 != NULL && e1->face != NULL);

                if (e1 != NULL) {
                    edges[l].next = e1;
                    e1->prev = &edges[l];
                }

                HE_edge *e2 = &edges[i];
                do {
                    e2 = e2->next->pair;
                } while(e2 != NULL && e2->face != NULL);

                if (e2 != NULL) {
                    edges[l].prev = e2;
                    e2->next = &edges[l];
                }

                edges[l].face = NULL;
                edges[l].pair = &edges[i];

                l++;
            }
        }
    }

    std::cout << "Found [" << l - num_edges << "] boundary edges." << std::endl;
    num_edges = l;

    std::cout << "Found all pairs." << std::endl;

    for (unsigned int i = 0; i < num_edges; i++) {
        if (edges[i].pair != NULL && edges[i].prev == NULL) {
            //std::cout << "Found edge [" << i << "] without a prev." << std::endl;
        }
        if (edges[i].pair != NULL && edges[i].next == NULL) {
            //std::cout << "Found edge [" << i << "] without a next." << std::endl;
        }
    }

    calculate_normals();
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

    verts = new HE_vert[num_verts];
    faces = new Face[num_faces];
    edges = new HE_edge[num_edges];

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

void Model::display() {
    glBegin(GL_TRIANGLES);

    for (unsigned int i = 0; i < num_faces; i++) {
        faces[i].display();
    }

    glEnd();
}

std::set<HE_vert*> intersection(std::set<HE_vert*> set1, std::set<HE_vert*> set2) {
    std::set<HE_vert*> result = std::set<HE_vert*>();
    for (std::set<HE_vert*>::iterator it = set1.begin(); it != set1.end(); it++) {
        if (set2.find(*it) != set2.end()) {
            result.insert(*it);
        }
    }
    return result;
}

std::set<HE_vert*> one_ring(HE_edge *edge) {
    std::set<HE_vert*> result = std::set<HE_vert*>();
    HE_edge *e0 = edge,
            *e = e0;

    do {
        result.insert(e->pair->vert);
        e = e->pair->prev;
    } while(e != e0);

    return result;
}

std::set<HE_vert*> two_ring(HE_edge *edge) {
    std::set<HE_vert*> result = std::set<HE_vert*>();

    std::set<HE_vert*> first_ring = one_ring(edge);

    for (std::set<HE_vert*>::iterator it = first_ring.begin(); it != first_ring.end(); it++) {
        std::set<HE_vert*> temp_ring = one_ring((*it)->edge);
        for (std::set<HE_vert*>::iterator it = temp_ring.begin(); it != temp_ring.end(); it++) {
            result.insert(*it);
        }
    }

    return result;
}

void Model::calculate_normals() {
    for (unsigned int i = 0; i < num_verts; i++) {
        HE_edge *e0 = verts[i].edge, *e = e0;
        verts[i].normal = Vector(0,0,0);
        do {
            verts[i].normal = verts[i].normal + e->face->normal();
            e = e->pair->prev;
        } while(e != e0);
        verts[i].normal = verts[i].normal.unit();
    }
}
