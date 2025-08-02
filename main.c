#include <stdio.h>
#include "packet_point.h"
#include "loop_algorithm.h"

int main() {
    // Tạo 5 gói tin mẫu
    point_nd packets[5];
    packets[0] = make_point("192.168.0.1", "10.0.0.2", 1000, 6, 0.1f);
    packets[1] = make_point("192.168.0.2", "10.0.0.3", 1050, 6, 0.15f);
    packets[2] = make_point("192.168.0.3", "10.0.0.4", 1100, 6, 0.12f);
    packets[3] = make_point("192.168.0.4", "10.0.0.5", 1150, 6, 0.2f);
    packets[4] = make_point("8.8.8.8",     "1.1.1.1",   500, 17, 0.9f);  // Gói tin bất thường (UDP, khác biệt)

    int num_packets = 5;
    int k = 3; // Số lân cận gần nhất

    float loop_scores[5];

    // Tính toán điểm LoOP cho mỗi gói tin
    compute_loop_scores(packets, loop_scores, num_packets, k);

    // In kết quả
    for (int i = 0; i < num_packets; i++) {
        printf("Packet %d: LoOP score = %.6f\n", i, loop_scores[i]);
    }

    return 0;
}
