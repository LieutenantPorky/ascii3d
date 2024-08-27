#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

typedef struct point point;
struct point {
  float position[3];
  float *x;
  float *y;
  float *z;
};

typedef struct line line;
struct line {
  point vertex[2];
};

typedef struct tris tris;
struct tris {
  point vertex[3];
};

typedef struct transform_stack transform_stack;
typedef struct mesh mesh;
struct mesh {
  int ntris;
  tris *tris;
  transform_stack *local_transforms;
};

typedef struct wireframe wireframe;
struct wireframe {
  int nlines;
  line *lines;
};

point *new_point(float position[3]);
line *line_from_stream(float position[6]);
line *line_from_points(point a, point b);

tris *tris_from_stream(float position[9]);

wireframe *wireframe_from_stream(int nlines, float *position);

#endif // PRIMITIVES_H_
