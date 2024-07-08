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

typedef struct mesh mesh;
struct mesh {
  int ntris;
  tris *tris;
};

point *new_point(float position[3]);
line *line_from_stream(float position[6]);
line *line_from_points(point a, point b);

tris *tris_from_stream(float position[9]);

#endif // PRIMITIVES_H_
