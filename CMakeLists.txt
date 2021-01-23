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
  server_src/actions/change_weapon_cuchillo.cpp
  server_src/actions/use_door.cpp
  server_src/games/game_manager.cpp
  server_src/items/item.cpp
  server_src/communication/message.cpp
  server_src/communication/message_processor.cpp
  server_src/communication/thread_client.cpp
  server_src/communication/thread_acceptor.cpp
  server_src/games/player.cpp
  server_src/games/game_status.cpp
  server_src/games/thread_game.cpp
  server_src/games/vector.cpp
  server_src/games/door.cpp
  server_src/client.cpp
  server_src/server_main.cpp
  server_src/server.cpp
  server_src/weapons/arma.cpp
  server_src/weapons/ametralladora.cpp
  server_src/weapons/canionDeCadena.cpp
  server_src/weapons/cuchillo.cpp
  server_src/weapons/pistola.cpp
  server_src/weapons/lanzaCohetes.cpp
  server_src/items/item.cpp
  server_src/items/arma_ametralladora.cpp
  server_src/items/arma_canion.cpp
  server_src/items/arma_lanzacohetes.cpp
  server_src/items/blood.cpp
  server_src/items/bullets.cpp
  server_src/items/food.cpp
  server_src/items/key.cpp
  server_src/items/medkit.cpp
  server_src/items/treasure.cpp
)

target_link_libraries(tp SDL2 SDL2_image pthread)

