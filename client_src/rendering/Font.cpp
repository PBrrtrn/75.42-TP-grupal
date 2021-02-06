#include "Font.h"

#define PTSIZE 36

Font::Font(std::string filepath) : font(NULL) {
	this->font = TTF_OpenFont(filepath.c_str(), PTSIZE);
	if (this->font == NULL) throw FontConstructorError(SDL_GetError());
}

Font::~Font() {
	TTF_CloseFont(this->font);
}

void Font::render(SDL_Renderer* renderer, std::string text,
									int x, int y, float scale, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
	if (surface == NULL) throw 1; // Lanzar un error apropiado

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) throw 1;

	int width = surface->w;
	int height = surface->h;

	SDL_FreeSurface(surface);

	SDL_Rect destination { x - width/2, y - height/2, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &destination);

	SDL_DestroyTexture(texture);
}

FontConstructorError::FontConstructorError(const char *ttf_error) noexcept {
  snprintf(this->error_msg, ERROR_BUF_LEN, 
           "Failed to construct font: %s", ttf_error);
}

FontConstructorError::~FontConstructorError() noexcept { }

const char* FontConstructorError::what() const noexcept {
  return this->error_msg;
}
