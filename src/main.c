#include "main.h"
#include "draw.h"
#include "primitives.h"
#include "transforms.h"
#include <stdio.h>

extern float *BUFFER_Z;

void print_point(point *in_point) {
  printf("[%f, %f, %f]", *(in_point->x), *(in_point->y), *(in_point->z));
}

void print_line(line *in_line) {
  print_point(in_line->vertex);
  printf("--");
  print_point(in_line->vertex + 1);
  printf("\n");
}

void print_wire(wireframe *in_wire) {
  printf("{");
  for (int i = 0; i < in_wire->nlines; i++) {
    printf("\t");
    print_line(in_wire->lines + i);
  }
  printf("}\n");
}

void debug_cube() {
  float cube[] = {
      -10, -10, 10,  10,  -10, 10,  -10, -10, 10,  -10, 10,  10,
      10,  10,  10,  10,  -10, 10,  10,  10,  10,  -10, 10,  10,

      -10, -10, -10, 10,  -10, -10, -10, -10, -10, -10, 10,  -10,
      10,  10,  -10, 10,  -10, -10, 10,  10,  -10, -10, 10,  -10,

      -10, -10, 10,  -10, -10, -10, 10,  -10, 10,  10,  -10, -10,
      10,  10,  10,  10,  10,  -10, -10, 10,  10,  -10, 10,  -10,

  };

  transform *translation = get_translation(25, 30, 30);
  transform *x_shift = get_translation(32, 0, 0);
  transform *y_rot = get_y_rotation(-3.1415 / 16);
  transform *z_rot = get_z_rotation(-3.1415 / 4);

  for (int i = 0; i < 4; i++) {
    wireframe *cube_wire = wireframe_from_stream(12, cube);
    transform *base = get_x_rotation(-3.1415 / 4);
    for (int j = 0; j < i; j++) {
      base = combine_transform(y_rot, base);
    }
    base = combine_transform(z_rot, base);
    base = combine_transform(translation, base);
    for (int j = 0; j < i; j++) {
      base = combine_transform(x_shift, base);
    }
    transform_wireframe(cube_wire, base);
    draw_wireframe(cube_wire);
  }
}

int main(int argc, char *argv[]) {

  float p_tris[] = {
      1., 1., 0., 60., 5., 0., 40., 50., 0.,
  };

  float p_tris_flat[] = {
      15., 1., 0., 15., 40., 0., 60., 50., 0.,
  };
  tris *test_tris = tris_from_stream(p_tris_flat);
  transform *base = get_z_rotation(3.1415 / 4);
  transform_tris(test_tris, base);

  init_graphics();
  /* debug_cube(); */
  draw_tris(test_tris);
  /* draw_tris_edge(test_tris); */
  update_screen();

  while (true) {
  }
}
