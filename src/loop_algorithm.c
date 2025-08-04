#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "loop_algorithm.h"
#include "data_point.h"

#define DEFAULT_LAMBDA  3.0f
#define SQRT2           1.41421356f
#define DEBUG           1 // <== bật hoặc tắt log ở đây

void find_k_nearest_neighbors_dp(const data_point* data, int num_points, int k, int knn_indices[][k]) {
    for (int i = 0; i < num_points; i++) {
        float dist[num_points];
        for (int j = 0; j < num_points; j++) {
            dist[j] = (i == j) ? 1e9 : standard_distance_data(&data[i], &data[j]);
        }

        printf("Point %d:\n", i);
        for (int m = 0; m < k; m++) {
            int min_idx = -1;
            float min_val = 1e9;
            for (int j = 0; j < num_points; j++) {
                if (dist[j] < min_val) {
                    min_val = dist[j];
                    min_idx = j;
                }
            }
            knn_indices[i][m] = min_idx;
            printf("  Neighbor %d: index=%d, distance=%.4f\n", m, min_idx, min_val);
            dist[min_idx] = 1e9;
        }
        printf("\n");
    }
}

void probabilistic_set_distance_dp(const data_point* data, int num_points, int k, int knn_indices[][k], float* pdist) {
    for (int i = 0; i < num_points; i++) {
        float sum = 0.0f;
        for (int j = 0; j < k; j++) {
            int neighbor_idx = knn_indices[i][j];
            float d = standard_distance_data(&data[i], &data[neighbor_idx]);
            sum += d * d;
        }
        pdist[i] = sqrtf(sum / k);
    }

#if DEBUG
    printf("\nProbabilistic distances (pdist):\n");
    for (int i = 0; i < num_points; i++) {
        printf("pdist[%d] = %.4f\n", i, pdist[i]);
    }
#endif
}

void compute_plof(const float* pdist, int num_points, int k, int knn_indices[][k], float* plof) {
    for (int i = 0; i < num_points; i++) {
        float avg_neighbor_pdist = 0.0f;
        for (int j = 0; j < k; j++) {
            int neighbor_idx = knn_indices[i][j];
            avg_neighbor_pdist += pdist[neighbor_idx];
        }
        avg_neighbor_pdist /= k;

        if (avg_neighbor_pdist > 1e-6f)
            plof[i] = (pdist[i] / avg_neighbor_pdist) - 1.0f;
        else
            plof[i] = 0.0f;
    }

#if DEBUG
    printf("\nPLOF values:\n");
    for (int i = 0; i < num_points; i++) {
        printf("plof[%d] = %.4f\n", i, plof[i]);
    }
#endif
}

float compute_nplof(const float* plof, int num_points, float lambda) {
    float sum_sq = 0.0f;
    for (int i = 0; i < num_points; i++) {
        sum_sq += plof[i] * plof[i];
    }
    float mean_sq = sum_sq / num_points;
    float nplof = lambda * sqrtf(mean_sq);

#if DEBUG
    printf("\nnPLOF (normalized PLOF): %.4f\n", nplof);
#endif

    return nplof;
}

void compute_loop_scores(const float* plof, int num_points, float nplof, float* loop_out) {
    for (int i = 0; i < num_points; i++) {
        float val = plof[i] / (nplof * SQRT2);
        float score = erf(val);
        loop_out[i] = fmaxf(0.0f, fminf(1.0f, score));
    }

#if DEBUG
    printf("\nLoOP scores:\n");
    for (int i = 0; i < num_points; i++) {
        printf("LoOP[%d] = %.4f\n", i, loop_out[i]);
    }
#endif
}

void run_loop_dp(const data_point* data, int num_points, int k, float* loop_out) {
    int knn_indices[num_points][k];
    float pdist[num_points];
    float plof[num_points];

#if DEBUG
    printf("\n--- RUNNING LoOP on %d data points, k = %d ---\n", num_points, k);
#endif

    find_k_nearest_neighbors_dp(data, num_points, k, knn_indices);
    probabilistic_set_distance_dp(data, num_points, k, knn_indices, pdist);
    compute_plof(pdist, num_points, k, knn_indices, plof);
    float nplof = compute_nplof(plof, num_points, DEFAULT_LAMBDA);
    compute_loop_scores(plof, num_points, nplof, loop_out);

#if DEBUG
    printf("\n--- END LoOP ---\n\n");
#endif
}
