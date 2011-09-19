#include "controller.hpp"

#include <GL/glut.h>

#include "view.hpp"
#include "player.hpp"

static std::pair<double,double> mouse_pos;
static int left_button_state;

void controller_mouseButtonFunc(int button, int state, int x, int y) {
    static std::pair<double,double> mouse_initial_pos;
    if (button == GLUT_LEFT_BUTTON) {
        mouse_pos = std::pair<int,int>(x, y);
        left_button_state = state;
        if (state == GLUT_DOWN) {
            mouse_initial_pos = std::pair<int,int>(x, y);
            glutSetCursor(GLUT_CURSOR_NONE);
        } else {
            glutWarpPointer(mouse_initial_pos.first, mouse_initial_pos.second);
            glutSetCursor(GLUT_CURSOR_INHERIT);
        }
    }
}

void controller_mouseMotionFunc(int x, int y) {
    if (left_button_state == GLUT_DOWN) {
        std::pair<double,double> rotation = std::pair<double,double>(
            (x - mouse_pos.first) / (double) width,
            (y - mouse_pos.second) / (double) height
        );
        
        player_turn(rotation);
        
        if (x < 0) {
            x = width;
            glutWarpPointer(x, y);
        } else if (x > width) {
            x = 0;
            glutWarpPointer(x, y);
        }

        if (y < 0) {
            y = height;
            glutWarpPointer(x, y);
        } else if (y > height) {
            y = 0;
            glutWarpPointer(x, y);
        }
    }

    mouse_pos = std::pair<int, int>(x, y);
    glutPostRedisplay();
}
