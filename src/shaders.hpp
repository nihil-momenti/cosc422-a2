#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <string>

#include <GL/glew.h>

extern GLuint shaders_init_program(const std::string &vert_shader, const std::string &frag_shader);

extern void shaders_next();

#endif
