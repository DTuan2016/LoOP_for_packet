#include <stdio.h>
#include "data_point.h"
#include "loop_algorithm.h"

int main() {
    // Tạo 5 gói tin mẫu (4 bình thường + 1 bất thường)
    // point_nd packets[5];
    // packets[0] = make_point("192.168.0.1", "10.0.0.2", 1000, 6, 0.1f);
    // packets[1] = make_point("192.168.0.2", "10.0.0.3", 1050, 6, 0.15f);
    // packets[2] = make_point("192.168.0.3", "10.0.0.4", 1100, 6, 0.12f);
    // packets[3] = make_point("192.168.0.4", "10.0.0.5", 1150, 6, 0.2f);
    // packets[4] = make_point("8.8.8.8",     "1.1.1.1",   500, 17, 0.9f); // Gói bất thường

    data_point points[5];
    points[0] = make_data_point(120, 5);
    points[1] = make_data_point(135, 4);
    points[2] = make_data_point(800, 7);
    points[3] = make_data_point(95000, 150);
    points[4] = make_data_point(300, 100);

    int num_points = 5;
    int k = 4; // Số lân cận gần nhất
    float loop_scores[5];

    // Gọi hàm run đã viết trong loop_algorithm.c
    run_loop_dp(points, num_points, k, loop_scores);

    // In kết quả
    for (int i = 0; i < num_points; i++) {
        printf("Point %d: LoOP score = %.6f\n", i, loop_scores[i]);
    }

    return 0;
}
