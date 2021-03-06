cmake_minimum_required(VERSION 3.15)

project(TPGrupal)

add_executable(Client client_src/main.cpp)
add_executable(Server server_src/server.cpp)
<<<<<<< HEAD
add_executable(WolfEditor editor_src/WolfEditor/main.cpp)
#add_executable(ServerConfigGenerator server_src/server_config_generator.cpp)
#add_executable(ServerClientTest server_src/server_clienttest.cpp)
=======
>>>>>>> ee2e82b5a19bc6f213896720603e437994a00a8e
add_subdirectory(client_src)
add_subdirectory(server_src)
add_subdirectory(common_src)
add_subdirectory(editor_src/WolfEditor)

set(CMAKE_BUILD_TYPE Debug)

<<<<<<< HEAD
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

target_link_libraries(Client client-classes common-classes yaml-cpp SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_link_libraries(Server server-classes common-classes yaml-cpp pthread)
target_link_libraries(WolfEditor editor-classes Qt5::Core Qt5::Widgets yaml-cpp)
#target_link_libraries(ServerConfigGenerator server-classes common-classes pthread yaml-cpp)
#target_link_libraries(ServerClientTest common-classes yaml-cpp pthread)
=======
target_link_libraries(Client client-classes common-classes yaml-cpp SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_link_libraries(Server server-classes common-classes yaml-cpp pthread)
>>>>>>> ee2e82b5a19bc6f213896720603e437994a00a8e
