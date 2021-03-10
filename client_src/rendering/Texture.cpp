#include <vector>

#include <iostream>
#include "Texture.h"

#define DVAL 180

Texture::Texture(SDL_Renderer* renderer, const char *filepath)
: texture(NULL) {
  SDL_Surface* surface = NULL; // Usar la clase surface
  surface = IMG_Load(filepath);
  if (surface == NULL) {
    throw 1; // Lanzar un error apropiado
  }

  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (this->texture == NULL) throw TextureConstructorError(SDL_GetError());

  SDL_FreeSurface(surface);

  SDL_QueryTexture(this->texture, &this->format, NULL, &this->width, &this->height);
}

Texture::~Texture() {
  SDL_DestroyTexture(this->texture);
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect *clip, SDL_Rect *dest) {
  SDL_RenderCopy(renderer, this->texture, clip, dest);
}

void Texture::renderTexels(SDL_Renderer* renderer,
                           std::vector<float>& z_buffer,
                           float z_depth, int x_pos, int y_pos,
                           int width, int height) {
  int start_x = x_pos - (width/2);
  int end_x = x_pos + (width/2);

  for (int texel_x = start_x; texel_x < end_x; texel_x++) {
    if (z_depth < z_buffer[texel_x]) {
      float texel = float(texel_x - start_x) / float(end_x - start_x);
      this->renderTexel(renderer, texel_x, texel, 480, height, 0);
    }
  }
}

void Texture::renderTexel(SDL_Renderer* renderer, int x, float texel, 
                          int screen_height, int length, int darken) {
  if (darken == 1) SDL_SetTextureColorMod(this->texture, DVAL, DVAL, DVAL);
  else SDL_SetTextureColorMod(this->texture, 255, 255, 255);

  SDL_Rect texture_source { int(texel * this->width), 0, 1, this->height };
  SDL_Rect screen_destination { x, (screen_height - length)/2, 1, length };

  this->render(renderer, &texture_source, &screen_destination);
}

int Texture::getWidth() {
  return this->width;
}

int Texture::getHeight() {
  return this->height;
}

TextureConstructorError::TextureConstructorError
                (const char *sdl_error) noexcept {
  snprintf(this->error_msg, ERROR_BUF_LEN, 
           "Failed to initialize SDL_Texture: %s", sdl_error);
}

TextureConstructorError::~TextureConstructorError() noexcept { }

const char* TextureConstructorError::what() const noexcept {
  return this->error_msg;
}
