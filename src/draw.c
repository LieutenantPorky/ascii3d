#include "draw.h"
#include "primitives.h"
#include <curses.h>

// Init and finish functions
void init_graphics() {
  signal(SIGINT, finish); /* arrange interrupts to terminate */
  initscr();              /* initialize the curses library */
  keypad(stdscr, TRUE);   /* enable keyboard mapping */
  nonl();                 /* tell curses not to do NL->CR/NL on output */
  cbreak();               /* take input chars one at a time, no wait for \n */
  noecho();               /* echo input - in color */

  if (has_colors()) {
    start_color();
  }
  curs_set(0);
}

void finish(int sig) {
  endwin();
  exit(0);
};

void update_screen() { refresh(); }

void draw_point(int x, int y) {
  int y_size;
  y_size = getmaxy(stdscr);
  mvaddch(y_size - y, x, '@');
}

void _draw_line_q1(line *in_line) {
  int x0, y0, x1, y1;
  if (*(in_line->vertex[0].x) <= *(in_line->vertex[1].x)) {
    x0 = (int)*(in_line->vertex[0].x);
    y0 = (int)*(in_line->vertex[0].y);
    x1 = (int)*(in_line->vertex[1].x);
    y1 = (int)*(in_line->vertex[1].y);
  } else {
    x1 = (int)*(in_line->vertex[0].x);
    y1 = (int)*(in_line->vertex[0].y);
    x0 = (int)*(in_line->vertex[1].x);
    y0 = (int)*(in_line->vertex[1].y);
  }
  int x = x0;
  int y = y0;
  int A = 2 * (y1 - y0);
  int B = -2 * (x1 - x0);
  int d = A + 1 / (2 * B);
  while (x <= x1) {
    draw_point(x, y);
    if (d > 0) {
      y++;
      d += B;
    }

    x++;
    d += A;
  }
}

void _draw_line_q8(line *in_line) {
  int x0, y0, x1, y1;
  if (*(in_line->vertex[0].x) <= *(in_line->vertex[1].x)) {
    x0 = (int)*(in_line->vertex[0].x);
    y0 = (int)*(in_line->vertex[0].y);
    x1 = (int)*(in_line->vertex[1].x);
    y1 = (int)*(in_line->vertex[1].y);
  } else {
    x1 = (int)*(in_line->vertex[0].x);
    y1 = (int)*(in_line->vertex[0].y);
    x0 = (int)*(in_line->vertex[1].x);
    y0 = (int)*(in_line->vertex[1].y);
  }
  int x = x0;
  int y = y0;
  int A = 2 * (y1 - y0);
  int B = -2 * (x1 - x0);
  int d = A + 1 / (2 * B);
  while (x <= x1) {
    draw_point(x, y);
    if (d < 0) {
      y--;
      d -= B;
    }

    x++;
    d += A;
  }
}

void _draw_line_q2(line *in_line) {
  int x0, y0, x1, y1;
  if (*(in_line->vertex[0].y) <= *(in_line->vertex[1].y)) {
    x0 = (int)*(in_line->vertex[0].x);
    y0 = (int)*(in_line->vertex[0].y);
    x1 = (int)*(in_line->vertex[1].x);
    y1 = (int)*(in_line->vertex[1].y);
  } else {
    x1 = (int)*(in_line->vertex[0].x);
    y1 = (int)*(in_line->vertex[0].y);
    x0 = (int)*(in_line->vertex[1].x);
    y0 = (int)*(in_line->vertex[1].y);
  }
  int x = x0;
  int y = y0;
  int A = 2 * (y1 - y0);
  int B = -2 * (x1 - x0);
  int d = B + 1 / (2 * A);
  while (y <= y1) {
    draw_point(x, y);
    if (d > 0) {
      x++;
      d += A;
    }

    y++;
    d += B;
  }
}

void _draw_line_q7(line *in_line) {
  int x0, y0, x1, y1;
  if (*(in_line->vertex[0].y) <= *(in_line->vertex[1].y)) {
    x0 = (int)*(in_line->vertex[0].x);
    y0 = (int)*(in_line->vertex[0].y);
    x1 = (int)*(in_line->vertex[1].x);
    y1 = (int)*(in_line->vertex[1].y);
  } else {
    x1 = (int)*(in_line->vertex[0].x);
    y1 = (int)*(in_line->vertex[0].y);
    x0 = (int)*(in_line->vertex[1].x);
    y0 = (int)*(in_line->vertex[1].y);
  }
  int x = x0;
  int y = y0;
  int A = 2 * (y1 - y0);
  int B = -2 * (x1 - x0);
  int d = B + 1 / (2 * A);
  while (y <= y1) {
    draw_point(x, y);
    if (d > 0) {
      x--;
      d -= A;
    }

    y++;
    d += B;
  }
}

void draw_line(line *in_line) {
  float dx = *(in_line->vertex[0].x) - *(in_line->vertex[1].x);
  float dy = *(in_line->vertex[0].y) - *(in_line->vertex[1].y);
  if (dx * dy >= 0) { /*Positive slope*/
    if (dx * dx >= dy * dy) {
      _draw_line_q1(in_line);
    } else {
      _draw_line_q2(in_line);
    }
  } else {
    if (dx * dx >= dy * dy) {
      _draw_line_q8(in_line);
    } else {
      _draw_line_q7(in_line);
    }
  }
}

void draw_tris_edge(tris *in_tris) {
  line *a = line_from_points(in_tris->vertex[0], in_tris->vertex[1]);
  line *b = line_from_points(in_tris->vertex[1], in_tris->vertex[2]);
  line *c = line_from_points(in_tris->vertex[2], in_tris->vertex[0]);

  draw_line(a);
  draw_line(b);
  draw_line(c);
}
