#pragma once

#include <assert.h>


#include "entity.h"
#include "game.h"

using namespace sf;
using namespace std;

struct ship : public entClass {
	const float SHIPACCELL = 0.4f; // inpulse accellation
	const int MAXBULLETS = 64;
	int activeBullets = 0; // bullets in the bullet pool currently active
	float shootCooldown = -0.1; // time in seconds between shots still to wait (can only fire when negative)
	const float MAXSHOOTCOOLDOWN = 0.2; // shortest time in seconds between shots
	const int BULLETSPEED = 400;
	const int BULLETOFFSETX = 60; // where bullets firefrom, relative to ship origin
	const int BULLETOFFSETY = 28;



	void doShipMovement();

	entClass* getBulletFromPool(entStore*);

	void shoot(Textures*, entStore*, float);

	void doOtherPlrInput(Textures*, entStore*, float);
};
