#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>

typedef enum {
    FORWARD,
    LEFT,
    RIGHT,
    BACK,
    UP,
    DOWN
} Direction;

extern void player_init();
extern void player_move(Direction);
extern void player_stop(Direction);
extern void player_turn(std::pair<double,double>);
extern void player_look();

#endif
