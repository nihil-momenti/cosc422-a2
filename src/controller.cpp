#include "controller.hpp"

#include <GL/glut.h>
#include <algorithm>

#include "view.hpp"
#include "shaders.hpp"
#include "player.hpp"

extern void controller_mouseButtonFunc(int,int,int,int);
extern void controller_mouseMotionFunc(int,int);
extern void controller_keyboardFunc(unsigned char,int,int);
extern void controller_keyboardUpFunc(unsigned char,int,int);
extern void controller_keyboardFunc_dvorak(unsigned char,int,int);
extern void controller_keyboardUpFunc_dvorak(unsigned char,int,int);

void controller_init(int argc, char *argv[], bool dvorak) {
    player_init();
    view_init(argc, argv);

    shaders_init_program("shaders/three-tone.vert", "shaders/three-tone.frag");
    shaders_init_program("shaders/phong.vert", "shaders/phong.frag");
//    shaders_next();

    glutIgnoreKeyRepeat(GL_TRUE);

    glutDisplayFunc(view_display);
    glutReshapeFunc(view_reshape);
    glutMouseFunc(controller_mouseButtonFunc);
    glutMotionFunc(controller_mouseMotionFunc);
    if (dvorak) {
        glutKeyboardFunc(controller_keyboardFunc_dvorak);
        glutKeyboardUpFunc(controller_keyboardUpFunc_dvorak);
    } else {
        glutKeyboardFunc(controller_keyboardFunc);
        glutKeyboardUpFunc(controller_keyboardUpFunc);
    }
}

void controller_run() {
    glutMainLoop();
}
