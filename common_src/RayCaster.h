#ifndef PRUEBA_SDL_RAYCASTER_H
#define PRUEBA_SDL_RAYCASTER_H
#include <vector>
#include "Vector.h"
#include "Map.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>


#define CELL_WIDTH 64
#define CELL_HEIGHT 64

class RayCaster {
public:
    RayCaster();
    ~RayCaster();
    Vector getIntersection(Vector playerPosition, Vector playerDirection);
    float getWallHeight(Vector playerPosition, Vector playerDirection,
                        float centerAngle, int& wall_texture);
    int getWallTextureAt(Vector position,Vector direction);


private:
    void getBounds(float x_i,float y_i,float x_dir,float y_dir,float& top_boundary,float& bottom_boundary,float& left_boundary,float& right_boundary);
    void collisionAgainstBounds(float x_i,float y_i,float x_dir,float y_dir,float top_boundary,float bottom_boundary,float left_boundary,float right_boundary,float& x_c,float& y_c);
    bool findCollision(float x_i,float y_i,float x_dir,float y_dir,float& x_c,float& y_c);
    Map map;
    float findFirstHorizontalDistance(Vector &playerPosition, float angle);
    float findFirstVerticalDistance(Vector &playerPosition, float angle);
    bool isWall(Vector &position);

};


#endif //PRUEBA_SDL_RayCaster_H
