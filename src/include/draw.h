#ifndef DRAW_H_
#define DRAW_H_

#include "primitives.h"
#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void init_graphics();
void finish(int sig);
void draw_point(int x, int y);
void draw_line(line *in_line);
void draw_tris_edge(tris *in_tris);
void draw_wireframe(wireframe *in_wireframe);
void draw_tris(tris *in_tris);
void update_screen();

#endif // DRAW_H_
