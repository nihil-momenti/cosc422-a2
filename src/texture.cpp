#include "texture.hpp"

#include <math.h>

#include <GL/glut.h>

GLuint tex_id;

static const unsigned int TEX_SIZE = 16;
static const unsigned int TEX_LAYERS = 4;

void texture_init() {
    unsigned char *tex= new unsigned char[TEX_SIZE*TEX_SIZE*TEX_LAYERS*3];

    for (unsigned int i = 0; i < TEX_LAYERS; i++) {
        for (unsigned int j = 0; j < TEX_SIZE; j++) {
            for (unsigned int k = 0; k < TEX_SIZE; k++) {
                if ((j % (unsigned int)pow(2,i)) == 0) {
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * (i))) + 0] = 0;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * (i))) + 1] = 0;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * (i))) + 2] = 0;
                } else {
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * (i))) + 0] = 255;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * (i))) + 1] = 255;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * (i))) + 2] = 255;
                }
            }
        }
    }

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_3D, tex_id);

    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, TEX_SIZE, TEX_SIZE, TEX_LAYERS, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_3D);
}
