#include "view.hpp"

#include <glew.h>
#include <GL/glut.h>

#include "common.hpp"
#include "player.hpp"
#include "shaders.hpp"
#include "lights.hpp"
#include "time.hpp"
#include "texture.hpp"
#include "sphere.hpp"

double fov    = 50.0,
       near   = 0.1,
       far    = 100.0,
       aspect = 0.0;

int height = 0,
    width = 0;

static bool view_show_fps = false;

static const unsigned int NUM_FRAMES = 5;
static double frame_times[NUM_FRAMES];
static double frame_starts[NUM_FRAMES];
static unsigned int frame_count;

static unsigned int sphere_list;

void view_init(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Assignment 2, Wim Looman");

    glewInit();

    GLuint pencil_program = shaders_init_program("shaders/pencil.vert", "shaders/pencil.frag");
    shaders_init_program("shaders/three-tone.vert", "shaders/three-tone.frag");
    shaders_init_program("shaders/phong.vert", "shaders/phong.frag");
    shaders_next();

    lights_init();
    texture_init(pencil_program);
    model.gl_init();
    sphere_list = sphere_gl_init(3, 0.5);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glLineWidth(2.0);
    glEnable(GL_LINE_SMOOTH);
}

void view_reshape(int new_width, int new_height) {
    glViewport(0, 0, new_width, new_height);
    width = new_width;
    height = new_height;
    aspect = new_width / (double)new_height;
}

void view_toggle_fps() {
    view_show_fps = !view_show_fps;
}

static void display_fps(double start_time, double end_time) {
    frame_starts[frame_count] = start_time;
    frame_times[frame_count] = end_time - start_time;
    if (++frame_count == NUM_FRAMES) {
        frame_count = 0;
        double render_time = 0.0;
        double actual_time = 0.0;
        for (unsigned int i = 0; i < NUM_FRAMES; i++) {
            render_time += frame_times[i] / NUM_FRAMES;
        }
        for (unsigned int i = 1; i < NUM_FRAMES; i++) {
            actual_time += (frame_starts[i] - frame_starts[i-1]) / (NUM_FRAMES - 1);
        }
        double render_fps = 1 / render_time;
        double actual_fps = 1 / actual_time;
        std::cout << "Current render FPS: [" << (int)render_fps << "]   \t Current actual FPS: [" << (int)actual_fps << "]" << std::endl;
    }
}

void view_display() {
    double start_time, end_time;

    if (view_show_fps) { start_time = time_get(); }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    player_look();

    lights_display();

    glPolygonMode(GL_FRONT, GL_FILL);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glColor4f(0.44, 0.31, 0.21, 1.0);

    sphere_display(sphere_list);
    model.display();

    glPolygonMode(GL_BACK, GL_LINE);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_FRONT);
    glColor4f(0.0, 0.0, 0.0, 1.0);

    sphere_display(sphere_list);
    model.display();

    glutSwapBuffers();

    if (view_show_fps) {
        end_time = time_get();
        display_fps(start_time, end_time);
    }
}
