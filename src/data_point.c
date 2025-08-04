#include "data_point.h"
#include <arpa/inet.h>
#include <math.h>

data_point make_data_point(const uint32_t pps, const uint32_t fps){
    data_point p;
    p.pps = pps;
    p.fps = fps;
    return p;
}

float standard_distance_data(const data_point* p1, const data_point* p2){
    uint32_t ans = 0;
    uint32_t pps_binh = (p1->pps - p2->pps) * (p1->pps - p2->pps);
    uint32_t fps_binh = (p1->fps - p2->fps) * (p1->fps - p2->fps);
    ans = pps_binh + fps_binh;
    return sqrtf(ans);
}