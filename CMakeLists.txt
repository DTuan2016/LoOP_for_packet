cmake_minimum_required(VERSION 3.10)
project(loop_algorithm C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(loop_algorithm
    main.c
    src/loop_algorithm.c
    src/packet_point.c
)

target_link_libraries(loop_algorithm m) 
