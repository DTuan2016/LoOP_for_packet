#ifndef LOOP_ALGORITHM_H
#define LOOP_ALGORITHM_H
#include <stdio.h>
#include <packet_point.h>
// using namespace std;
#define SUCCESS     1
#define FAIL        0
// #define DIM         5

#define DEFAULT_LAMBDA 3.0f  // hệ số lambda dùng trong LoOP
static float squared_distance(const point_nd* a, const point_nd* b);
static float probabilistic_distance(const point_nd* p, point_nd* all_points, int total_points, int k);
void compute_loop_scores(point_nd* points, float* loop_scores, int total_points, int k);

#endif // LOOP_ALGORITHM_H