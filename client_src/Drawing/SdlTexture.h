#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <string>
#include <SDL2/SDL.h>

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
public:
    /**
     * Crea un SDL_Texture, lanza una excepción si el filename es inválido
     **/
    SdlTexture(const std::string &filename, const SdlWindow& window);
    /**
     * Libera la memoria reservada por la textura
     **/
    ~SdlTexture();
    /**
     * Renderiza la textura cargada
     **/
    void render(const Area& src, const Area& dest) const;
    void render(SDL_Rect* clip, const Area& dest);
private:
    SDL_Texture* loadTexture(const std::string &filename);
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int mHeight;
    int mWidth;
};

#endif
