#include "draw.h"
#include "primitives.h"
#include <curses.h>
#include <stdlib.h>

float *BUFFER_Z;
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
  BUFFER_Z = calloc(getmaxx(stdscr) * getmaxy(stdscr), sizeof(float));
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
    if (d < 0) {
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
  if (dx * dx < 1 && dy * dy < 1) { /*Line smaller than single pixel*/
    draw_point((int)*(in_line->vertex[0].x), (int)*(in_line->vertex[0].y));
    return;
  }
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

  free(a);
  free(b);
  free(c);
}

void draw_wireframe(wireframe *in_wireframe) {
  for (int i = 0; i < in_wireframe->nlines; i++) {
    draw_line(in_wireframe->lines + i);
  }
}

int order_points(const void *a, const void *b) {
  float ay = ((point *)a)->position[1];
  float by = ((point *)b)->position[1];
  if (ay > by) {
    return 1;
  }
  if (ay == by) {
    return 0;
  }
  return -1;
}

void draw_horizontal(int x0, int x1, int y) {
  if (x0 > x1) {
    int x_tmp = x0;
    x0 = x1;
    x1 = x_tmp;
  }
  for (int x_curr = x0; x_curr <= x1; x_curr++) {
    draw_point(x_curr, y);
  }
}

void draw_tris(tris *in_tris) {
  float zt, zm, zb;
  /*Backface culling if AxB.C <=0, C = (0,0,1) */
  float zn = (*(in_tris->vertex[0].x) - *(in_tris->vertex[1].x)) *
                 (*(in_tris->vertex[2].y) - *(in_tris->vertex[1].y)) -
             (*(in_tris->vertex[0].y) - *(in_tris->vertex[1].y)) *
                 (*(in_tris->vertex[2].x) - *(in_tris->vertex[1].x));

  if (zn <= 0) {
    /* return; */
  }
  /*Order vertices according to y value*/
  point vertices[3];
  vertices[0] = in_tris->vertex[0];
  vertices[1] = in_tris->vertex[1];
  vertices[2] = in_tris->vertex[2];

  qsort(vertices, 3, sizeof(point), order_points);
  /*
    draw_point(*vertices[0].x, *vertices[0].y);
    draw_point(*vertices[1].x, *vertices[1].y);
    draw_point(*vertices[2].x, *vertices[2].y);
  */
  float x0 = (float)*vertices[0].x;
  float x1 = (float)*vertices[0].x;
  int xt = *vertices[2].x;
  int xm = *vertices[1].x;
  int xb = *vertices[0].x;
  int yt = *vertices[2].y;
  int ym = *vertices[1].y;
  int yb = *vertices[0].y;

  float dx0 = (xt - xb) / (float)(yt - yb);
  float dx1 = (xm - xb) / (float)(ym - yb);
  float dx1_1 = (xt - xm) / (float)(yt - ym);

  for (int y = yb; y <= yt; y++) {
    draw_horizontal(x0, x1, y);
    x0 += dx0;
    x1 += dx1;
    if (y == ym) {
      dx1 = dx1_1;
      x1 = xm;
    }
  }
}
