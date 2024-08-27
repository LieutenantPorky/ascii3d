#include "transforms.h"
#include <math.h>

transform *get_translation(float x, float y, float z) {
  transform *out_transform = calloc(1, sizeof(transform));
  out_transform->matrix[0][0] = 1;
  out_transform->matrix[1][1] = 1;
  out_transform->matrix[2][2] = 1;
  out_transform->matrix[3][3] = 1;

  out_transform->matrix[0][3] = x;
  out_transform->matrix[1][3] = y;
  out_transform->matrix[2][3] = z;

  return out_transform;
}

transform *get_z_rotation(float angle) {
  transform *out_transform = calloc(1, sizeof(transform));
  out_transform->matrix[0][0] = cosf(angle);
  out_transform->matrix[0][1] = sinf(angle);
  out_transform->matrix[1][0] = -1 * sinf(angle);
  out_transform->matrix[1][1] = cosf(angle);

  out_transform->matrix[2][2] = 1;
  out_transform->matrix[3][3] = 1;

  return out_transform;
}

transform *get_x_rotation(float angle) {
  transform *out_transform = calloc(1, sizeof(transform));
  out_transform->matrix[1][1] = cosf(angle);
  out_transform->matrix[1][2] = -1 * sinf(angle);
  out_transform->matrix[2][1] = sinf(angle);
  out_transform->matrix[2][2] = cosf(angle);

  out_transform->matrix[0][0] = 1;
  out_transform->matrix[3][3] = 1;

  return out_transform;
}

transform *get_y_rotation(float angle) {
  transform *out_transform = calloc(1, sizeof(transform));
  out_transform->matrix[0][0] = cosf(angle);
  out_transform->matrix[0][2] = -1 * sinf(angle);
  out_transform->matrix[2][0] = sinf(angle);
  out_transform->matrix[2][2] = cosf(angle);

  out_transform->matrix[1][1] = 1;
  out_transform->matrix[3][3] = 1;

  return out_transform;
}

transform *combine_transform(transform *left, transform *right) {
  transform *out_transform = calloc(1, sizeof(transform));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        out_transform->matrix[i][j] += left->matrix[i][k] * right->matrix[k][j];
      }
    }
  }

  return out_transform;
}

void transform_point(point *in_point, transform *t) {
  float result[] = {0, 0, 0, 0};
  float pos[] = {0, 0, 0, 0};
  pos[0] = in_point->position[0];
  pos[1] = in_point->position[1];
  pos[2] = in_point->position[2];
  pos[3] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i] += t->matrix[i][j] * pos[j];
    }
  }

  for (int i = 0; i < 3; i++) {
    in_point->position[i] = result[i];
  }
}

void transform_line(line *in_line, transform *t) {
  transform_point(&(in_line->vertex[0]), t);
  transform_point(&(in_line->vertex[1]), t);
}

void transform_tris(tris *in_tris, transform *t) {
  transform_point(&(in_tris->vertex[0]), t);
  transform_point(&(in_tris->vertex[1]), t);
  transform_point(&(in_tris->vertex[2]), t);
}

void transform_wireframe(wireframe *in_wireframe, transform *t) {
  for (int i = 0; i < in_wireframe->nlines; i++) {
    transform_line(in_wireframe->lines + i, t);
  }
}
