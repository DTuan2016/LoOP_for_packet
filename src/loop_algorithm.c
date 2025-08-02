#include <stdlib.h>
#include <math.h>
#include "loop_algorithm.h"
#include "packet_point.h"

#define DEFAULT_LAMBDA 3.0f  // hệ số lambda dùng trong LoOP

// Hàm tính khoảng cách Euclidean bình phương giữa 2 điểm
static float squared_distance(const point_nd* a, const point_nd* b) {
    float dist = 0.0f;
    dist += powf(a->packet_size - b->packet_size, 2);
    dist += powf(a->protocol - b->protocol, 2);
    dist += powf(a->flow_duration - b->flow_duration, 2);
    return dist;
}

// Tính RkNN (root mean square distance tới k điểm gần nhất)
static float probabilistic_distance(const point_nd* p, point_nd* all_points, int total_points, int k) {
    float* distances = (float*)malloc(sizeof(float) * total_points);
    for (int i = 0; i < total_points; i++) {
        distances[i] = euclidean_distance(p, &all_points[i]);
    }

    // Sắp xếp các khoảng cách tăng dần
    for (int i = 0; i < total_points - 1; i++) {
        for (int j = i + 1; j < total_points; j++) {
            if (distances[i] > distances[j]) {
                float tmp = distances[i];
                distances[i] = distances[j];
                distances[j] = tmp;
            }
        }
    }

    // Lấy trung bình bình phương k khoảng cách gần nhất
    float sum = 0.0f;
    for (int i = 0; i < k && i < total_points; i++) {
        sum += distances[i] * distances[i];
    }
    free(distances);

    float rms = sqrtf(sum / k);
    return rms;
}

// Hàm tính toán điểm LoOP cho từng điểm trong mảng
void compute_loop_scores(point_nd* points, float* loop_scores, int total_points, int k) {
    float* pdist = (float*)malloc(sizeof(float) * total_points);

    // Bước 1: Tính khoảng cách chuẩn hoá PDIST (probabilistic distance) cho mỗi điểm
    for (int i = 0; i < total_points; i++) {
        pdist[i] = probabilistic_distance(&points[i], points, total_points, k);
    }

    // Bước 2: Tính LoOP score
    for (int i = 0; i < total_points; i++) {
        float sum = 0.0f;
        int neighbors = 0;

        for (int j = 0; j < total_points; j++) {
            if (i == j) continue;
            float dist = euclidean_distance(&points[i], &points[j]);
            sum += powf(dist / (pdist[i] + pdist[j] + 1e-5f), 2);
            neighbors++;
        }

        float pld = sqrtf(sum / neighbors);
        loop_scores[i] = erf(DEFAULT_LAMBDA * pld); // Giới hạn từ 0 đến 1
    }

    free(pdist);
}
