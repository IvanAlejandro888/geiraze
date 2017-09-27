cmake_minimum_required(VERSION 2.6)
project(geiraze_alpha_1)

add_executable(geiraze main.cpp fileman.cpp charman.cpp codecman.cpp debugman.cpp)

install(TARGETS geiraze RUNTIME DESTINATION bin)
