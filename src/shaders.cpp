#include "shaders.hpp"

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <glew.h>
#include <GL/glut.h>

GLuint vert_shader,
       frag_shader,
       program;

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

void printShaderInfo(GLuint shader) {
    int length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];

    glGetShaderInfoLog(shader, length, NULL, infoLog);

    std::cout << "Shader info log:" << std::endl << infoLog << std::endl << std::endl;
}

void printProgramInfo(GLuint program) {
    int length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];

    glGetProgramInfoLog(program, length, NULL, infoLog);

    std::cout << "Program info log:" << std::endl << infoLog << std::endl << std::endl;
}

void shaders_init() {
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vert_source = readShader("shaders/three-tone.vert");
    const char *frag_source = readShader("shaders/three-tone.frag");

    glShaderSource(vert_shader, 1, &vert_source, NULL);
    glShaderSource(frag_shader, 1, &frag_source, NULL);

    glCompileShader(vert_shader);
    glCompileShader(frag_shader);

    printShaderInfo(vert_shader);
    printShaderInfo(frag_shader);

    delete[] vert_source;
    delete[] frag_source;

    program = glCreateProgram();

    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);

    glLinkProgram(program);
    glUseProgram(program);

    printProgramInfo(program);
}

void shaders_display() {
}
