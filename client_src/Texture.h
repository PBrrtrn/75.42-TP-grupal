#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <exception>

class Texture {
private:
  SDL_Texture* texture;
  int width;
  int height;
  uint32_t format;
public:
  Texture(SDL_Renderer* renderer, const char *filepath);
  ~Texture();
  Texture(const Texture&) = delete;            // Saco el constructor por copia
  Texture& operator=(const Texture&) = delete; // Saco la asignacion por copia
  void render(SDL_Renderer* renderer, SDL_Rect *clip, SDL_Rect *dst);
  void renderTexel(SDL_Renderer* renderer, int x, float texel, 
                   int screen_height, int length, int side);
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