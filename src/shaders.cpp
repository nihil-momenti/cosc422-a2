#include "shaders.hpp"

#include <glew.h>
#include <GL/glut.h>

#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>

static std::vector<GLuint> programs;
static unsigned int current_program;

static unsigned int measure_file(std::ifstream &file) {
    file.seekg(0, std::ios::end);
    unsigned int length = file.tellg();
    file.seekg(0, std::ios::beg);
    return length;
}

static char * read_shader(const std::string &file) {
    std::ifstream input;

    input.open(file.c_str());
    if (input.fail()) {
        std::cout << "Error opening shader file [" << file << "]" << std::endl;
        exit(1);
    }

    unsigned int length = measure_file(input);
    char *buffer = new char[length + 1];

    input.read(buffer, length);
    input.close();
    buffer[length] = '\0';

    return buffer;
}

static void printShaderInfo(GLuint shader) {
    int length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];

    glGetShaderInfoLog(shader, length, NULL, infoLog);

    std::cout << "Shader info log:" << infoLog << std::endl;
}

static void printProgramInfo(GLuint program) {
    int length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];

    glGetProgramInfoLog(program, length, NULL, infoLog);

    std::cout << "Program info log:" << infoLog << std::endl;
}

static GLuint shaders_init_shader(const std::string path, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);

    const char *source = read_shader(path);
    glShaderSource(shader, 1, &source, NULL);
    delete[] source;

    glCompileShader(shader);
    printShaderInfo(shader);

    return shader;
}

GLuint shaders_init_program(const std::string &vert_path, const std::string &frag_path) {
    GLuint vert_shader = shaders_init_shader(vert_path, GL_VERTEX_SHADER);
    GLuint frag_shader = shaders_init_shader(frag_path, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();

    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);

    glLinkProgram(program);
    printProgramInfo(program);

    programs.push_back(program);
    return program;
}

void shaders_next() {
    current_program = (current_program + 1) % programs.size();
    glUseProgram(programs[current_program]);
    glutPostRedisplay();
}
