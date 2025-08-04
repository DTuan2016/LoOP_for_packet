#include <stdio.h>
#include "data_point.h"
#include "loop_algorithm.h"

int main() {
    data_point points[30] = {
        make_data_point(120, 5),
        make_data_point(135, 4),
        make_data_point(110, 6),
        make_data_point(140, 5),
        make_data_point(125, 4),
        make_data_point(130, 5),
        make_data_point(118, 6),
        make_data_point(119, 5),
        make_data_point(122, 5),
        make_data_point(128, 4),

        make_data_point(130, 5),
        make_data_point(121, 6),
        make_data_point(124, 5),
        make_data_point(137, 5),
        make_data_point(115, 5),
        make_data_point(126, 4),
        make_data_point(123, 5),
        make_data_point(129, 4),
        make_data_point(134, 5),
        make_data_point(117, 6),

        make_data_point(132, 5),
        make_data_point(138, 4),
        make_data_point(116, 6),
        make_data_point(127, 5),
        make_data_point(133, 4),
        make_data_point(136, 5),
        make_data_point(131, 4),
        make_data_point(139, 5),
        make_data_point(119, 6),

        // Dữ liệu bất thường (anomaly)
        make_data_point(5000, 200)
    };
    int num_points = 30;
    int k = 3; // Số lân cận gần nhất
    float loop_scores[30];

    // Gọi hàm run đã viết trong loop_algorithm.c
    run_loop_dp(points, num_points, k, loop_scores);

    // In kết quả
    for (int i = 0; i < num_points; i++) {
        printf("Point %d: LoOP score = %.6f\n", i, loop_scores[i]);
    }

    return 0;
}
