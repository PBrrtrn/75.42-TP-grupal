cmake_minimum_required(VERSION 3.15)

project(TPGrupal)

add_executable(Client client_src/main.cpp)
add_executable(Server server_src/server.cpp)
add_executable(WolfEditor editor_src/WolfEditor/main.cpp)

add_subdirectory(client_src)
add_subdirectory(server_src)
add_subdirectory(common_src)
add_subdirectory(editor_src/WolfEditor)

set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

target_link_libraries(Client client-classes common-classes yaml-cpp SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_link_libraries(Server server-classes common-classes yaml-cpp pthread)
target_link_libraries(WolfEditor editor-classes Qt5::Core Qt5::Widgets yaml-cpp)
