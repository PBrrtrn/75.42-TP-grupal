#include "Drawer.h"



Drawer::Drawer() : window(SCREEN_WIDTH, SCREEN_HEIGHT) {

}

Drawer::~Drawer() {}

void Drawer::renderColumn(Vector position, float auxAngle, float angle, int x) {
	int height, wall_texture;
	height = rc.getWallHeight(position, Vector(auxAngle), angle, wall_texture);

	int y = SCREEN_HEIGHT / 2 - height / 2;
    
    //std::cout << " height:" << height << " y:" << y << std::endl;
    
    //Area newArea(x, y, 1, height);
    Area newArea(x, y, 1, height);

	SDL_Rect rect;
	rect.x = newArea.getX();
	rect.y = newArea.getY();
	rect.w = newArea.getWidth();
	rect.h = newArea.getHeight();
	SDL_RenderDrawRect(this->window.getRenderer(), &rect);

	//SDL_SetRenderDrawColor(this->window.getRenderer(), 34,34,180,0xFF);
	//SDL_SetRenderDrawColor(this->window.getRenderer(), 34,34,180,0);
	
	int r=20,g=30,b=100;
	
	if (wall_texture == 1)
		r = 100; g=0; b=0;
	if (wall_texture == 2)
		r = 0; g=100; b=0;
	if (wall_texture == 3)
		r = 0; g=0; b=100;
	if (wall_texture == 4)
		r = 100; g=0; b=100;
	if (wall_texture > 4)
		r = 100; g=100; b=100;
	
	
	//std::cout << "" << wall_texture ;
	
	SDL_SetRenderDrawColor(this->window.getRenderer(), r,g,b,0);
}

void Drawer::draw(GameStatus &gStatus, int clientID) {
	this->window.fill();
	this->window.renderBackground();
	
	// Needed for render Column
	Vector position = gStatus.getPosition(clientID);
	float angle = gStatus.getAngle(clientID);
	float auxAngle = angle + FOV / 2;	
	//float auxAngle = angle + 
	//				(SCREEN_WIDTH / 2) * FOV / SCREEN_WIDTH;

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		this->renderColumn(position, auxAngle, angle, i);
		auxAngle -= ((float)FOV / (float)SCREEN_WIDTH);
		//auxAngle -= (FOV / 320);
	}
	
	//std::cout << " " << std::endl ;

	this->window.render();
}
