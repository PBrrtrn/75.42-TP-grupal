cmake_minimum_required(VERSION 3.15)

project(TPGrupal)

add_executable(Client client_src/main.cpp)
add_subdirectory(client_src)
add_subdirectory(common_src)

set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(Client client_classes common_classes yaml-cpp SDL2 SDL2_image)