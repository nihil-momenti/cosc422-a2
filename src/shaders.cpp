#include "shaders.hpp"

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const char *readShader(std::string file) {
    std::ifstream input;
    unsigned int length;
    char *buffer;

    input.open(file.c_str());
    if (input.fail()) {
        std::cout << "Error opening shader file" << std::endl;
        exit(1);
    }

    input.seekg(0, std::ios::end);
    length = input.tellg();
    input.seekg(0, std::ios::beg);

    buffer = new char[length + 1];
    input.read(buffer, length);
    input.close();

    buffer[input.gcount()] = '\0';

    std::cout << "Shader read successfully" << std::endl;

    return buffer;
}

void shaders_init() {
    GLuint vect_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vect_source = readShader("shaders/phong.vect");
    const char *frag_source = readShader("shaders/phong.frag");

    glShaderSource(vect_shader, 1, &vect_source, NULL);
    glShaderSource(frag_shader, 1, &frag_source, NULL);

    glCompileShader(vect_shader);
    glCompileShader(frag_shader);

    GLuint program = glCreateProgram();

    glAttachShader(program, vect_shader);
    glAttachShader(program, frag_shader);

    glLinkProgram(program);
    glUseProgram(program);

    delete[] vect_source;
    delete[] frag_source;
}
