#include <iostream>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Texture.h"
#include "Animation.h"

Renderer::Renderer(const char* title,
                   int width, int height,
                   EventQueue& event_queue) 
: renderer(NULL), window(title, width, height), event_queue(event_queue) {
  /* No me vuelve loco la idea de tener que estar haciendo pasamano de los
    atributos de Window. Capaz sería mejor inicializar la ventana desde
    afuera en el GameLoop y pasarla por movimiento para que el Renderer
    tenga ownership sin necesitar saber crearla. 
                                            - Pablo (06/12/2020)        */
  this->renderer = this->window.getRenderer();
  if (this->renderer == NULL) throw RendererConstructorError(SDL_GetError());

  SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    std::cout << "Warning: Could not set SDL hints" << std::endl;
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(this->renderer);
  IMG_Quit();
  this->join();
}

void Renderer::run() {
  Animation animation(this->renderer, "foo.png", 64, 205, 4); // Placeholder

  while (true) {
    int event = this->event_queue.pop();

    if (event == QUIT) {
      break;
    } else {
      SDL_RenderClear(this->renderer);
      animation.renderNextFrame(this->renderer, 1, 0, 0);
      SDL_RenderPresent(this->renderer);
    }

  }
}

RendererConstructorError::RendererConstructorError
                (const char *sdl_error) noexcept {
  snprintf(this->error_msg, ERROR_BUF_LEN, 
           "Failed to initialize SDL_Renderer: %s", sdl_error);
}

RendererConstructorError::~RendererConstructorError() noexcept { }

const char* RendererConstructorError::what() const noexcept {
  return this->error_msg;
}
