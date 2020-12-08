#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, const char *filepath)
: texture(NULL) {
	SDL_Surface* surface = NULL; // Usar la clase surface
	surface = IMG_Load(filepath);
	if (surface == NULL) throw 1;

	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (this->texture == NULL) throw TextureConstructorError(SDL_GetError());

	SDL_FreeSurface(surface);
}

Texture::~Texture() {
	SDL_DestroyTexture(this->texture);
}

void Texture::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, this->texture, NULL, NULL); // Aca tienen que ir las dimensiones del render
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
