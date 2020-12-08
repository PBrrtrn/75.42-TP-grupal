#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <exception>

class Texture {
private:
	SDL_Texture* texture;
public:
	Texture(SDL_Renderer* renderer, const char *filepath);
	~Texture();
	void render(SDL_Renderer* renderer);
};

#define ERROR_BUF_LEN 256

class TextureConstructorError : public std::exception {
private:
	char error_msg[ERROR_BUF_LEN];
public:
	explicit TextureConstructorError(const char* sdl_error) noexcept;
	virtual const char* what() const noexcept;
	virtual ~TextureConstructorError() noexcept;
};

#endif