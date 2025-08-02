#ifndef PACKET_POINT_H
#define PACKET_POINT_H

#include <stdint.h>

#define MAX_PACKET_SIZE     1500.0f
#define MAX_IP_VALUE        4294967295.0f
#define MAX_PROTOCOL        255.0f

// Số chiều vector đặc trưng
#define DIM 5

typedef struct point_nd {
    // float features[DIM];
    float       src_ip, dst_ip;
    uint16_t    packet_size;
    uint8_t     protocol;
    float       flow_duration;
} point_nd;

// Chuyển IP chuỗi sang uint32_t
uint32_t ip_str_to_int(const char* ip_str);

// Chuẩn hóa IP về [0, 1]
float normalize_ip(uint32_t ip);

// Chuẩn hóa kích thước packet
float normalize_size(uint16_t size);

// Chuẩn hóa giao thức (protocol)
float normalize_protocol(uint8_t proto);

// Tạo point_nd từ thông tin gói tin
point_nd make_point(const char* src_ip, const char* dst_ip,
                    uint16_t packet_size, uint8_t protocol,
                    float flow_duration);

// Tính khoảng cách Euclidean giữa hai điểm
float euclidean_distance(const point_nd* p1, const point_nd* p2);

#endif // PACKET_POINT_H
