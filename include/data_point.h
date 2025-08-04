#ifndef DATA_POINT_H
#define DATA_POINT_H

#include <stdint.h>

#define MAX_PACKET_SIZE     1500.0f
#define MAX_IP_VALUE        4294967295.0f
#define MAX_PROTOCOL        255.0f

// typedef struct point_nd {
//     float       src_ip, dst_ip;
//     uint16_t    packet_size;
//     uint8_t     protocol;
//     float       flow_duration;
// } point_nd;

typedef struct data_point{
    uint32_t pps; // packet per second
    uint32_t fps; //flow per second
} data_point;

// // Chuyển IP chuỗi sang uint32_t
// uint32_t ip_str_to_int(const char* ip_str);

// // Chuẩn hóa IP về [0, 1]
// float normalize_ip(uint32_t ip);

// // Chuẩn hóa kích thước packet
// float normalize_size(uint16_t size);

// // Chuẩn hóa giao thức (protocol)
// float normalize_protocol(uint8_t proto);

// // Tạo point_nd từ thông tin gói tin
// point_nd make_point(const char* src_ip, const char* dst_ip,
//                     uint16_t packet_size, uint8_t protocol,
//                     float flow_duration);

// // Tính khoảng cách Euclidean giữa hai điểm
// float standard_distance(const point_nd* p1, const point_nd* p2);

data_point make_data_point(const uint32_t pps, const uint32_t fps); 
float standard_distance_data(const data_point* p1, const data_point* p2);

#endif // DATA_POINT_H