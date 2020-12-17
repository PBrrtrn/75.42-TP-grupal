#include <iostream>
#include <SDL2/SDL.h>

#include "GameLoop.h"

int main(int argc, char *argv[]) {
  /* TODO: Leer del Yaml las texturas,
     mapas y dimensiones de la ventana principal */
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("Failed to initialize SDL");
    // throw SDLInitializationError(SDL_GetError());
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    std::cout << "Warning: Could not set render scale quality" << std::endl;
  GameLoop game_loop;
  game_loop.run();
}