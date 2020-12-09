#include "RayCaster.h"



RayCaster::RayCaster() {
	
	MapData md("map-data.yml");
	Map m(md);
	
	this->map = m;
	
    /*this->map ={
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,0,0,0,0,1,0,0,0,1},
                    {1,0,0,0,0,0,0,0,0,1},
                    {1,0,0,0,1,0,1,0,0,1},
                    {1,0,0,0,1,0,1,0,0,1},
                    {1,0,0,0,1,0,1,0,0,1},
                    {1,0,0,0,1,0,1,0,0,1},
                    {1,0,0,0,1,0,1,0,0,1},
                    {1,0,0,0,0,0,0,0,0,1},
                    {1,1,1,1,1,1,1,1,1,1}
            };*/
}

RayCaster::~RayCaster() {}

void RayCaster::getBounds(float x_i,float y_i,float x_dir,float y_dir,float& top_boundary,float& bottom_boundary,float& left_boundary,float& right_boundary){
	
	bool top_found = false;
	bool right_found = false;

	if (y_dir > 0) {
		//busco la pared superior e inferior de la grilla que limitan a mi punto
		for (int i=0; i <= (this->map.getHeight() * CELL_HEIGHT) && !top_found; i = i + CELL_HEIGHT) {
			if (y_i < i ){
				top_boundary = i;
				top_found = true;
			}
			else
				bottom_boundary = i;
		}	
	} else {
		//busco la pared superior e inferior de la grilla que limitan a mi punto
		for (int i=(this->map.getHeight() * CELL_HEIGHT); i > 0  && !top_found; i = i - CELL_HEIGHT) {
			if (y_i > i){
				bottom_boundary = i;
				top_found = true;
			}
			else
				top_boundary = i;	
		}			
	}

	if (x_dir > 0) {
		//busco la pared izq y der de la grilla que limitan a mi punto
		for (int i=0; i <= (this->map.getWidth() * CELL_WIDTH) && !right_found; i = i + CELL_WIDTH) {
			if (x_i < i || (x_i == i && x_dir < 0)){
				right_boundary = i;
				right_found = true;
			}
			else
				left_boundary = i;
		}
	} else {
		//busco la pared izq y der de la grilla que limitan a mi punto
		for (int i=(this->map.getWidth() * CELL_WIDTH); i > 0 && !right_found; i = i - CELL_WIDTH) {
			if (x_i > i ){
				left_boundary = i;
				right_found = true;
			}
			else
				right_boundary = i;
		}
	}
	

	//std::cout << " top:" << top_boundary <<" bottom:" << bottom_boundary <<" left:" << left_boundary <<" right:" << right_boundary << std::endl ;
	
}

void RayCaster::collisionAgainstBounds(float x_i,float y_i,float x_dir,float y_dir,float top_boundary,float bottom_boundary,float left_boundary,float right_boundary,float& x_c,float& y_c){
	
	float lambda;
	float x_c_top;
	float x_c_bottom;
	float y_c_left;
	float y_c_right;
	bool top_valid;
	bool bottom_valid;
	bool left_valid;
	bool right_valid;	
	
	//checkeo colision contra top
	//x_i,y_i,x_dir,y_dir,top_boundary
	lambda = (top_boundary - y_i)/y_dir;
	top_valid = lambda > 0;
	x_c_top = lambda*x_dir + x_i;
		
	//checkeo colision contra bottom
	//x_i,y_i,x_dir,y_dir,bottom_boundary
	lambda = (bottom_boundary - y_i)/y_dir;
	bottom_valid = lambda > 0;
	x_c_bottom = lambda*x_dir + x_i;		

	//checkeo colision contra left
	//x_i,y_i,x_dir,y_dir,left_boundary
	lambda = (left_boundary - x_i)/x_dir;
	left_valid = lambda > 0;
	y_c_left = lambda*y_dir + y_i;		

	//checkeo colision contra right
	//x_i,y_i,x_dir,y_dir,right_boundary
	lambda = (right_boundary - x_i)/x_dir;
	right_valid = lambda > 0;
	y_c_right = lambda*y_dir + y_i;	
		
	if (top_valid) {
		if (left_valid){
			if (x_c_top < left_boundary){
				x_c = left_boundary;
				y_c = y_c_left;
			}
			else {
				x_c = x_c_top;
				y_c = top_boundary;
			}
		}
		if (right_valid){
			if (x_c_top > right_boundary){
				x_c = right_boundary;
				y_c = y_c_right;
			} else {
				x_c = x_c_top;
				y_c = top_boundary;
			}
		}
	}
	if (bottom_valid){
		if (left_valid){
			if (x_c_bottom < left_boundary){
				x_c = left_boundary;
				y_c = y_c_left;
			}
			else {
				x_c = x_c_bottom;
				y_c = bottom_boundary;
			}
		}
		if (right_valid){
			if (x_c_bottom > right_boundary){
				x_c = right_boundary;
				y_c = y_c_right;
			} else {
				x_c = x_c_bottom;
				y_c = bottom_boundary;
			}
		}		
	}

}

int RayCaster::getWallTextureAt(Vector position,Vector direction){
	int x_i = position.getXCoordinate();
	int y_i = position.getYCoordinate();

	int x_dir = direction.getXCoordinate();
	int y_dir = direction.getYCoordinate();

	int x = ((int)x_i/CELL_WIDTH)%this->map.getWidth();
	//if (x_dir < 0)
	//	x = ((int)(x_i - 1)/CELL_WIDTH)%this->map.getWidth();
	int y = ((int)y_i/CELL_HEIGHT)%this->map.getHeight();
	//if (y_dir < 0)
	//	y = ((int)(y_i - 1)/CELL_HEIGHT)%this->map.getHeight();
	return this->map.getValue(x,y);
}

bool RayCaster::findCollision(float x_i,float y_i,float x_dir,float y_dir,float& x_c,float& y_c){

	int x = ((int)x_i/CELL_WIDTH)%this->map.getWidth();
	if (x_dir < 0)
		x = ((int)(x_i - 1)/CELL_WIDTH)%this->map.getWidth();
	int y = ((int)y_i/CELL_HEIGHT)%this->map.getHeight();
	if (y_dir < 0)
		y = ((int)(y_i - 1)/CELL_HEIGHT)%this->map.getHeight();
	if (this->map.getValue(x,y) != 0 )
		return false;
	
	float top_boundary,bottom_boundary,left_boundary,right_boundary;
	
	this->getBounds(x_i,y_i,x_dir,y_dir,top_boundary,bottom_boundary,left_boundary,right_boundary);
	this->collisionAgainstBounds(x_i,y_i,x_dir,y_dir,top_boundary,bottom_boundary,left_boundary,right_boundary,x_c,y_c);
	
	return true;

	
}

bool RayCaster::isWall(Vector &position) {
    int x = position.getXCoordinate();
    int y = position.getYCoordinate();
    
    int x_grid_location = (x/CELL_WIDTH)%this->map.getWidth();
    int y_grid_location = (y/CELL_HEIGHT)%this->map.getHeight();
    
    if (this->map.isWall(x_grid_location,y_grid_location) )
		return true;
    
    return false;

}


Vector RayCaster::getIntersection(Vector playerPosition,
                                  Vector playerDirection) {
    float angle = playerDirection.getAngle();
    playerDirection.turnUnitary();
    
    float x_c = playerPosition.getXCoordinate();
    float y_c = playerPosition.getYCoordinate();
    
    int fin = 0;
    while (findCollision(x_c,y_c,playerDirection.getXCoordinate(),playerDirection.getYCoordinate(),x_c,y_c) && fin < (this->map.getWidth() - 2)){
		fin++;
	}
	
	Vector posicionColision(x_c,y_c);

	return posicionColision;

}

float RayCaster::findFirstHorizontalDistance(Vector &playerPosition,
                                             float angle) {
    float playerY = playerPosition.getYCoordinate();
    int yPosition = ((int)playerY / CELL_HEIGHT) * CELL_HEIGHT;
    yPosition = sin(angle) > 0 ? yPosition + CELL_HEIGHT : yPosition;
    float ySide = abs(playerY - (float) yPosition);
    return abs(ySide / sin(angle));
}

float RayCaster::findFirstVerticalDistance(Vector &playerPosition,
                                           float angle) {
	//busco la coordenada en x
    float playerX = playerPosition.getXCoordinate();
    //mi posicion real respecto a la grilla donde estoy
    int xPosition = ((int)playerX / CELL_WIDTH) * CELL_WIDTH;
    // estoy mirando al este o el oeste?
    xPosition = cos(angle) > 0 ? xPosition + CELL_WIDTH : xPosition;
    // 
    float xSide = abs(playerX - (float) xPosition);
    return abs(xSide / cos(angle));

}

float RayCaster::getWallHeight(Vector playerPosition, Vector playerDirection,
                               float centerAngle, int& wall_texture) {
    Vector v = getIntersection(playerPosition, playerDirection);
    playerDirection.turnUnitary();

    Vector v2 = v + (playerPosition * -1);
    float distance = v2.calculateNorma();
    
    //std::cout << "distance:" << distance << std::endl;
    
    float  distortionAngle = centerAngle - playerDirection.getAngle();
    float perpDistance = abs(distance * cos(distortionAngle));
    //float perpDistance = abs(distance);
    
    wall_texture = this->getWallTextureAt(v,playerDirection);





    //TODO evitar distorsion
    
    //std::cout << "perpDistance" << perpDistance << std::endl;
    //std::cout << "perpDistance:" << perpDistance << " xpos:" << playerPosition.getXCoordinate() << " ypos:" << playerPosition.getYCoordinate() << std::endl;
    
    return (CELL_WIDTH / perpDistance) * CELL_WIDTH*4; //277
}
