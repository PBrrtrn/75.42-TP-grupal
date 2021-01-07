cmake_minimum_required(VERSION 2.8)

project(qt-sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (tp
  common_src/Map.cpp
  common_src/socket.cpp
  common_src/thread.cpp
  server_src/actions/action.cpp
  server_src/actions/move_backward.cpp
  server_src/actions/move_forward.cpp
  server_src/actions/move_left.cpp
  server_src/actions/move_right.cpp
  server_src/actions/shoot.cpp
  server_src/games/game_manager.cpp
  server_src/communication/thread_client.cpp
  server_src/communication/thread_acceptor.cpp
  server_src/games/game_status.cpp
  server_src/games/thread_game.cpp
  server_src/games/vector.cpp
  server_src/client.cpp
  server_src/server_main.cpp
  server_src/server.cpp
)

target_link_libraries(tp SDL2 SDL2_image pthread)

