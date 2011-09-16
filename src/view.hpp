#ifndef VIEW_HPP
#define VIEW_HPP

extern int height, width;

extern void view_init(int argc, char *argv[]);
extern void view_reshape(int new_width, int new_height);
extern void view_display();
extern void view_toggle_fps();

#endif
