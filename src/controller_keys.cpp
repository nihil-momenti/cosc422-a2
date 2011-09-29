#include "controller.hpp"

#include "common.hpp"
#include "view.hpp"
#include "player.hpp"
#include "shaders.hpp"
#include "sphere.hpp"

void controller_keyboardFunc(unsigned char key, int x, int y){
    switch(key) {
        case 'a': player_move(LEFT);        break;
        case 'w': player_move(FORWARD);     break;
        case 's': player_move(BACK);        break;
        case 'd': player_move(RIGHT);       break;
        case ' ': player_move(UP);          break;
        case 'z': player_move(DOWN);        break;

        case 'q': model.toggle_rotation();
                  sphere_toggle_rotation(); break;
        case 'e': view_toggle_fps();        break;
        case 'r': shaders_next();           break;
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

void controller_keyboardFunc_dvorak(unsigned char key, int x, int y){
    switch(key) {
        case 'a': player_move(LEFT);        break;
        case ',': player_move(FORWARD);     break;
        case 'o': player_move(BACK);        break;
        case 'e': player_move(RIGHT);       break;
        case ' ': player_move(UP);          break;
        case '\'': player_move(DOWN);       break;

        case ';': model.toggle_rotation();
                  sphere_toggle_rotation(); break;
        case '.': view_toggle_fps();        break;
        case 'p': shaders_next();           break;
    }
}

void controller_keyboardUpFunc_dvorak(unsigned char key, int x, int y){
    switch(key) {
        case 'a': player_stop(LEFT);     break;
        case ',': player_stop(FORWARD);  break;
        case 'o': player_stop(BACK);     break;
        case 'e': player_stop(RIGHT);    break;
        case ' ': player_stop(UP);       break;
        case '\'': player_stop(DOWN);     break;
    }
}
