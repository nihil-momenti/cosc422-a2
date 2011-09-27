#include "texture.hpp"

#include <GL/glut.h>

#include <math.h>

GLuint tex_id;

static const unsigned int TEX_SIZE = 1024;
static const unsigned int TEX_LAYERS = 4;

void texture_init(GLuint shader_program) {
    unsigned char *tex= new unsigned char[TEX_SIZE*TEX_SIZE*TEX_LAYERS*3];

    for (unsigned int i = 0; i < TEX_LAYERS; i++) {
        for (unsigned int j = 0; j < TEX_SIZE; j++) {
            for (unsigned int k = 0; k < TEX_SIZE; k++) {
                if ((j % 16) == 0 || (k % 16) == 0) {
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * i)) + 0] = 0;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * i)) + 1] = 0;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * i)) + 2] = 0;
                } else {
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * i)) + 0] = 255;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * i)) + 1] = 255;
                    tex[3*(k + TEX_SIZE * (j + TEX_LAYERS * i)) + 2] = 255;
                }
            }
        }
    }

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_3D, tex_id);

    GLint shader_texture_loc = glGetUniformLocation(shader_program, "texture");
    glUniform1i(shader_texture_loc, 0);

    GLint shader_texture_size_loc = glGetUniformLocation(shader_program, "texture_size");
    glUniform3f(shader_texture_size_loc, TEX_SIZE, TEX_SIZE, TEX_LAYERS);

    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, TEX_SIZE, TEX_SIZE, TEX_LAYERS, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_3D);
}
