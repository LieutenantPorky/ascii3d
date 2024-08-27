#ifndef TRANSFORMS_H_
#define TRANSFORMS_H_
#include "primitives.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct transform transform;
struct transform {
  float matrix[4][4];
};

typedef struct transform_stack transform_stack;
struct transform_stack {
  int n_transforms;
  transform transform[];
};

void transform_point(point *in_point, transform *t);
void transform_line(line *in_line, transform *t);
void transform_tris(tris *in_tris, transform *t);
void transform_wireframe(wireframe *in_wireframe, transform *t);

transform *get_translation(float x, float y, float z);
transform *get_z_rotation(float angle);
transform *get_x_rotation(float angle);
transform *get_y_rotation(float angle);
transform *combine_transform(transform *left, transform *right);
#endif // TRANSFORMS_H_
