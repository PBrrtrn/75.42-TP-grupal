#ifndef __FONT_H__
#define __FONT_H__

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Font {
private:
	TTF_Font *font;
public:
	Font(std::string filepath);
	~Font();
	void render(SDL_Renderer* renderer, std::string text, 
							int x, int y, float scale, SDL_Color color);
};

#define ERROR_BUF_LEN 256

class FontConstructorError : public std::exception {
private:
  char error_msg[ERROR_BUF_LEN];
public:
  explicit FontConstructorError(const char* ttf_error) noexcept;
  virtual const char* what() const noexcept;
  virtual ~FontConstructorError() noexcept;
};

#endif