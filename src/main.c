#include "main.h"
#include "draw.h"
#include "primitives.h"

int main(int argc, char *argv[]) {

  float p[] = {
      0., 40., 0., 20., 5., 0., 0., 0., 0.,
  };
  /* line *testline = line_from_stream(p); */
  tris *test_tris = tris_from_stream(p);

  init_graphics();

  /* draw_point(*(testline->vertex[0].x), *(testline->vertex[0].y)); */
  /* draw_point(*(testline->vertex[1].x), *(testline->vertex[1].y)); */
  /* draw_line(testline); */
  draw_tris_edge(test_tris);
  update_screen();

  while (true) {
  }
}
