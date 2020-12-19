#ifndef __RAYCASTER_H__
#define __RAYCASTER_H__

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "../common_src/Vector.h"
#include "../common_src/Map.h"


#define CELL_WIDTH 64
#define CELL_HEIGHT 64

class RayCaster {
public:
    RayCaster(Map& map);
    ~RayCaster();
    Vector getIntersection(Vector playerPosition, Vector playerDirection,int& wall_texture);
    /* float getWallHeight(Vector playerPosition, Vector playerDirection,
                        float centerAngle, int& wall_texture);    */
    int getWallTextureAt(Vector position,Vector direction);
private:
    Map& map;
    void getBounds(float x_i,float y_i,float x_dir,float y_dir,float& top_boundary,float& bottom_boundary,float& left_boundary,float& right_boundary);
    void collisionAgainstBounds(float x_i,float y_i,float x_dir,float y_dir,float top_boundary,float bottom_boundary,float left_boundary,float right_boundary,float& x_c,float& y_c);
    bool findCollision(float x_i,float y_i,float x_dir,float y_dir,float& x_c,float& y_c,int& wall_texture);
    float findFirstHorizontalDistance(Vector &playerPosition, float angle);
    float findFirstVerticalDistance(Vector &playerPosition, float angle);
    bool isWall(Vector &position);
};


#endif
