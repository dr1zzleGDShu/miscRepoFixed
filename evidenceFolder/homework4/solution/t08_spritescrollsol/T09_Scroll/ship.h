#pragma once

#include <assert.h>


#include "entity.h"
#include "game.h"

using namespace sf;
using namespace std;

struct ship : public entClass {
	const float SHIPACCELL = 0.4f;
	const int MAXBULLETS = 64;
	int activeBullets = 0;
	float shootCooldown = -0.1;
	const float MAXSHOOTCOOLDOWN = 0.2;
	const int BULLETSPEED = 400;
	const int BULLETOFFSETX = 60;
	const int BULLETOFFSETY = 28;



	void doShipMovement(int, int, int, int);

	entClass* getBulletFromPool(entStore*);

	void shoot(Textures*, entStore*, float);

	void doOtherPlrInput(Textures*, entStore*, float);
};
