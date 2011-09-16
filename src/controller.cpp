#include "controller.hpp"

#include <GL/glut.h>
#include <algorithm>

#include "common.hpp"
#include "view.hpp"
#include "player.hpp"

static std::pair<double,double> mouse_pos;
static int left_button_state;

static void controller_mouseButtonFunc(int,int,int,int);
static void controller_mouseMotionFunc(int,int);
static void controller_keyboardFunc(unsigned char,int,int);
static void controller_keyboardUpFunc(unsigned char,int,int);

void controller_init(int argc, char *argv[]) {
    player_init();
    view_init(argc, argv);

    glutIgnoreKeyRepeat(GL_TRUE);

    glutDisplayFunc(view_display);
    glutReshapeFunc(view_reshape);
    glutMouseFunc(controller_mouseButtonFunc);
    glutMotionFunc(controller_mouseMotionFunc);
    glutKeyboardFunc(controller_keyboardFunc);
    glutKeyboardUpFunc(controller_keyboardUpFunc);

    mouse_pos = std::pair<double,double>(0,0);
    left_button_state = GLUT_UP;
}

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

void controller_keyboardFunc(unsigned char key, int x, int y){
    switch(key) {
        case 'a': player_move(LEFT);        break;
        case 'w': player_move(FORWARD);     break;
        case 's': player_move(BACK);        break;
        case 'd': player_move(RIGHT);       break;
        case ' ': player_move(UP);          break;
        case 'z': player_move(DOWN);        break;

        case 'q': model.toggle_rotation();  break;
        case 'e': view_toggle_fps();        break;
    }
}

void controller_keyboardUpFunc(unsigned char key, int x, int y){
    switch(key) {
        case 'a': player_stop(LEFT);     break;
        case 'w': player_stop(FORWARD);  break;
        case 's': player_stop(BACK);     break;
        case 'd': player_stop(RIGHT);    break;
        case ' ': player_stop(UP);       break;
        case 'z': player_stop(DOWN);     break;
    }
}

void controller_run() {
    glutMainLoop();
}
