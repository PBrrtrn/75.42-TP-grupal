#ifndef DRAWER_H
#define DRAWER_H

#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "../RayCaster.h"
#include "../GameStatus.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 400
#define FOV 1.0472

//1.0472

class Drawer {

	SdlWindow window;
	RayCaster rc;
	void renderColumn(Vector position, float auxAngle, float angle, int x);
public:
	Drawer();
	~Drawer();
	void draw(GameStatus &gStatus, int clientID);
};

#endif // DRAWER_H
