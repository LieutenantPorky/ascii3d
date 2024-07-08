#include "primitives.h"
#include <stdlib.h>

point *_set_point(point *out_point, float position[3]) {
  out_point->position[0] = position[0];
  out_point->position[1] = position[1];
  out_point->position[2] = position[2];

  out_point->x = out_point->position;
  out_point->y = out_point->position + 1;
  out_point->z = out_point->position + 2;
  return out_point;
}

point *new_point(float position[3]) {
  point *out_point = malloc(sizeof(point));
  _set_point(out_point, position);
  return out_point;
}

line *line_from_stream(float position[6]) {
  line *out_line = malloc(sizeof(line));
  _set_point(out_line->vertex, position);
  _set_point(out_line->vertex + 1, position + 3);
  return out_line;
}

line *line_from_points(point a, point b) {
  line *out_line = malloc(sizeof(line));
  out_line->vertex[0] = a;
  out_line->vertex[1] = b;
  return out_line;
}

tris *tris_from_stream(float position[9]) {
  tris *out_tris = malloc(sizeof(tris));
  _set_point(out_tris->vertex, position);
  _set_point(out_tris->vertex + 1, position + 3);
  _set_point(out_tris->vertex + 2, position + 6);
  return out_tris;
}
