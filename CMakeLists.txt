cmake_minimum_required(VERSION 3.15)

project(TPGrupal)

add_executable(Client client_src/main.cpp)
add_executable(Server server_src/server.cpp)
add_executable(ServerConfigGenerator server_src/server_config_generator.cpp)
#add_executable(ServerClientTest server_src/server_clienttest.cpp)
add_subdirectory(client_src)
add_subdirectory(server_src)
add_subdirectory(common_src)

set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(Client client-classes common-classes yaml-cpp SDL2 SDL2_image SDL2_ttf)
target_link_libraries(Server server-classes common-classes yaml-cpp pthread)
target_link_libraries(ServerConfigGenerator server-classes common-classes pthread yaml-cpp)
#target_link_libraries(ServerClientTest common-classes yaml-cpp pthread)
