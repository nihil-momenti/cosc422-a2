#ifndef VIEW_HPP
#define VIEW_HPP

#include "main.hpp"
#include "model.hpp"

void view_init(int argc, char *argv[]);
void view_reshape(int new_width, int new_height);
void view_display();

int get_view_height();
int get_view_width();

void view_toggle_bcull();
void view_toggle_wireframe();
void view_reset();

#endif
