#include "texture.hpp"

#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>

#define WHITE() do {\
            tex[3*(k + (TEX_SIZE) * (j + (TEX_SIZE) * i)) + 0] = 255;\
            tex[3*(k + (TEX_SIZE) * (j + (TEX_SIZE) * i)) + 1] = 255;\
            tex[3*(k + (TEX_SIZE) * (j + (TEX_SIZE) * i)) + 2] = 255;\
        } while (false)

#define BLACK() do {\
            tex[3*(k + (TEX_SIZE) * (j + (TEX_SIZE) * i)) + 0] = 0;\
            tex[3*(k + (TEX_SIZE) * (j + (TEX_SIZE) * i)) + 1] = 0;\
            tex[3*(k + (TEX_SIZE) * (j + (TEX_SIZE) * i)) + 2] = 0;\
        } while (false)

GLuint tex_id;

static const unsigned int TEX_SIZE = 512;
static const unsigned int TEX_LAYERS = 8;

static void clear_tex(unsigned char *tex) {
    for (unsigned int i = 0; i < TEX_LAYERS; i++) {
        for (unsigned int j = 0; j < TEX_SIZE; j++) {
            for (unsigned int k = 0; k < TEX_SIZE; k++) {
                tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 0] = 255;
                tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 1] = 255;
                tex[3*(k + TEX_SIZE * (j + TEX_SIZE * i)) + 2] = 255;
            }
        }
    }
}

static void draw_horiz_line(unsigned char *tex, int layer, int width) {
    for (unsigned int row = 0; row < TEX_SIZE; row++) {
        tex[3*(width + TEX_SIZE * (row + TEX_SIZE * layer)) + 0] = 0;
        tex[3*(width + TEX_SIZE * (row + TEX_SIZE * layer)) + 1] = 0;
        tex[3*(width + TEX_SIZE * (row + TEX_SIZE * layer)) + 2] = 0;
    }
}

static void draw_vert_line(unsigned char *tex, int layer, int height) {
    for (unsigned int col = 0; col < TEX_SIZE; col++) {
        tex[3*(col + TEX_SIZE * (height + TEX_SIZE * layer)) + 0] = 0;
        tex[3*(col + TEX_SIZE * (height + TEX_SIZE * layer)) + 1] = 0;
        tex[3*(col + TEX_SIZE * (height + TEX_SIZE * layer)) + 2] = 0;
    }
}

static void draw_horiz_lines(unsigned char *tex, int top_layer) {
    int width = rand() % TEX_SIZE;
    for (int i = top_layer; i >= 0; i--) {
        draw_horiz_line(tex, i, width);
    }
}

static void draw_vert_lines(unsigned char *tex, int top_layer) {
    int height = rand() % TEX_SIZE;
    for (int i = top_layer; i >= 0; i--) {
        draw_vert_line(tex, i, height);
    }
}

static void fill_tex2(unsigned char *tex) {
    clear_tex(tex);
    for (int i = TEX_LAYERS-1; i >= 0; i--) {
        for (int j = pow(2.5,(TEX_LAYERS-2)); j >= pow(2.5,i); j--) {
            draw_horiz_lines(tex, i);
            //draw_vert_lines(tex, i);
        }
    }
}

static void fill_tex(unsigned char *tex) {
    for (unsigned int i = 0; i < TEX_LAYERS; i++) {
        for (unsigned int j = 0; j < TEX_SIZE; j++) {
            for (unsigned int k = 0; k < TEX_SIZE; k++) {
                int val = (int)(double)pow(2.0, (int)(i-1));
                if (i < 1 || ((j + 1) % val) == 0 || ((k + 1) % val) == 0) {
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
    unsigned char *tex= new unsigned char[(TEX_SIZE)*(TEX_SIZE)*(TEX_LAYERS)*3];

    fill_tex2(tex);

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
