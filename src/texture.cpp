#include "texture.hpp"

#include <GL/glut.h>

#include <math.h>

#define WHITE() do {\
            tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 0] = 255;\
            tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 1] = 255;\
            tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 2] = 255;\
        } while (false)

#define BLACK() do {\
            tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 0] = 0;\
            tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 1] = 0;\
            tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 2] = 0;\
        } while (false)

GLuint tex_id;

static const unsigned int TEX_SIZE = 512;
static const unsigned int TEX_LAYERS = 64;

static void fill_tex(unsigned char *tex) {
    for (unsigned int i = 0; i < TEX_LAYERS+2; i++) {
        for (unsigned int j = 0; j < TEX_SIZE+2; j++) {
            for (unsigned int k = 0; k < TEX_SIZE+2; k++) {
                int val = (int)(double)pow(2.0, (int)((i-1)/7));
                if (i/7 <= 1 || ((j + 1) % val) == 0 || ((k + 1) % val) == 0) {
                    BLACK();
                } else {
                    WHITE();
                }
            }
        }
    }
}

static void set_shader_variables(GLuint shader_program) {
    GLint old_program;

    glGetIntegerv(GL_CURRENT_PROGRAM, &old_program);
    glUseProgram(shader_program);

    GLint shader_texture_loc = glGetUniformLocation(shader_program, "texture");
    glUniform1i(shader_texture_loc, 0);

    glUseProgram(old_program);
}

void texture_init(GLuint shader_program) {
    unsigned char *tex= new unsigned char[(TEX_SIZE+2)*(TEX_SIZE+2)*(TEX_LAYERS+2)*3];

    fill_tex(tex);

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_3D, tex_id);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, TEX_SIZE, TEX_SIZE, TEX_LAYERS, 1, GL_RGB, GL_UNSIGNED_BYTE, tex);

    set_shader_variables(shader_program);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_3D);
}
