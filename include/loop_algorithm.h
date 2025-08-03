#ifndef LOOP_ALGORITHM_H
#define LOOP_ALGORITHM_H
#include <stdio.h>
#include <packet_point.h>
// using namespace std;
float standard_distance(const point_nd* a, const point_nd* b); 
void find_k_nearest_neighbors(const point_nd* data, int num_points, int k, int knn_indices[][k]);
void probabilistic_set_distance(const point_nd* data, int num_points, int k, int knn_indices[][k], float* pdist);
void compute_plof(const float* pdist, int num_points, int k, int knn_indices[][k], float* plof);
float compute_nplof(const float* plof, int num_points, float lambda);
void compute_loop_scores(const float* plof, int num_points, float nplof, float* loop_out);
void run_loop(const point_nd* data, int num_points, int k, float* loop_out);

#endif // LOOP_ALGORITHM_H