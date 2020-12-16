#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "SdlException.h"
#include "SdlWindow.h"
#include <iostream>


SdlWindow::SdlWindow(int width, int height) :
        width(width), height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    errCode = SDL_CreateWindowAndRenderer(
        width, height, SDL_RENDERER_ACCELERATED,
        &this->window, &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana", SDL_GetError());
    }   
}


SdlWindow::~SdlWindow() {
    std::cout << "Destruyendo" << std::endl;
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
    SDL_Rect rect;
    rect.x = this->height / 2;
    rect.y = this->width / 2;
    rect.w = this->width;
    rect.h = this->height/2;
    SDL_RenderDrawRect(this->renderer, &rect);

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    

}

void SdlWindow::fill() {
    this->fill(113,113,113,255);
    //this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::render() {
    SDL_RenderPresent(this->renderer);
}

void SdlWindow::renderBackground() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = this->width;
    rect.h = this->height/2;
    SDL_RenderDrawRect(this->renderer, &rect);

    SDL_SetRenderDrawColor(this->renderer, 56,56,56,0xFF);
    SDL_RenderFillRect(this->renderer, &rect);
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}
