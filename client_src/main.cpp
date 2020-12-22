#include <iostream>
#include <SDL2/SDL.h>

#include "GameLoop.h"

int main(int argc, char *argv[]) {
  /* TODO: Leer del Yaml las texturas,
     mapas y dimensiones de la ventana principal */
  GameLoop game_loop;
  game_loop.run();
}