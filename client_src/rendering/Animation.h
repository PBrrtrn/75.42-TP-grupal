#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "Texture.h"

class Animation {
private:
  std::vector<Texture*> frames;
public:
  Animation(SDL_Renderer* renderer, std::vector<std::string> frame_paths);
  ~Animation();
  void render(SDL_Renderer* renderer, int frame, int x_pos, int y_pos, 
              int width, int height);
  void renderTexels(SDL_Renderer* renderer, int frame, 
                    std::vector<float>& z_buffer, float z_depth, 
                    int x_pos, int y_pos, int width, int height);
  int framesCount();
};

#endif
