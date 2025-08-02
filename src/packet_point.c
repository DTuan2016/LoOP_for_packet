#include "packet_point.h"
#include <arpa/inet.h>
#include <math.h>

uint32_t ip_str_to_int(const char* ip_str) {
    struct in_addr ip_addr;
    inet_pton(AF_INET, ip_str, &ip_addr);
    return ntohl(ip_addr.s_addr);  // chuyển về host byte order
}

float normalize_ip(uint32_t ip) {
    return (float)ip / MAX_IP_VALUE;
}

float normalize_size(uint16_t size) {
    return (float)size / MAX_PACKET_SIZE;
}

float normalize_protocol(uint8_t proto) {
    return (float)proto / MAX_PROTOCOL;
}

point_nd make_point(const char* src_ip, const char* dst_ip,
                    uint16_t packet_size, uint8_t protocol,
                    float flow_duration) {
    point_nd p;
    uint32_t src = ip_str_to_int(src_ip);
    uint32_t dst = ip_str_to_int(dst_ip);

    p.src_ip = normalize_ip(src);
    p.dst_ip = normalize_ip(dst);
    p.packet_size = normalize_size(packet_size);
    p.protocol = normalize_protocol(protocol);
    p.flow_duration = flow_duration;  // Giả sử đã chuẩn hóa trước

    return p;
}

float euclidean_distance(const point_nd* p1, const point_nd* p2) {
    float sum = 0.0f;
    // sum = (p1->src_ip - p2->)
    float src_binh           = (p1->src_ip - p2->src_ip)*(p1->src_ip - p2->src_ip);
    float dst_binh           = (p1->dst_ip - p2->dst_ip)*(p1->dst_ip - p2->dst_ip);
    float packet_zize_binh   = (p1->packet_size - p2->packet_size)*(p1->packet_size - p2->packet_size);
    float protocol_binh      = (p1->protocol - p2->protocol)*(p1->protocol - p2->protocol);
    float flow_duration_binh = (p1->flow_duration - p2->flow_duration)*(p1->flow_duration - p2->flow_duration);
    
    // for (int i = 0; i < DIM; i++) {
    //     float diff = p1->features[i] - p2->features[i];
    //     sum += diff * diff;
    // }
    sum = src_binh + dst_binh + packet_zize_binh + protocol_binh + flow_duration_binh;
    return sqrt(sum);
}
