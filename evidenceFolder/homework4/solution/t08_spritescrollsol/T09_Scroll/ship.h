#pragma once

#include <assert.h>


#include "entity.h"
#include "game.h"

using namespace sf;
using namespace std;

struct ship : public entClass {
	const float SHIPACCELL = 0.15f;
	const int MAXBULLETS = 64;
	int activeBullets = 0;
	float shootCooldown = -0.1;
	const float MAXSHOOTCOOLDOWN = 0.2;
	const int BULLETSPEED = 200;


	void doShipMovement(int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
		int inputDirect[2] = {0,0};


		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			inputDirect[1] -= 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			inputDirect[1] += 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			inputDirect[0] -= 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			inputDirect[0] += 1;
		}
		cout << inputDirect[0] << inputDirect[1] << endl;

		accelEnt(inputDirect[0] * SHIPACCELL, inputDirect[1] * SHIPACCELL);
		//accelEnt(inputDirect[0] * SHIPSPEED * 1, inputDirect[1] * SHIPSPEED * 1);

		//setPos(100, 300);

	}


	entClass* getBulletFromPool(entStore* entStoreIn) {
		// for loops only work when there is a breakpoint in the fuction, for some reason 
		for (int i = 0; i < MAXBULLETS; i++){ 
			if (!(entStoreIn->bulletPtrPool.at(i)->isActive)) {
				/*if (i == 10) {
					std::cout << "make this line a breakpoint";
				*///}
				return entStoreIn->bulletPtrPool.at(i);
			}
		}
		return entStoreIn->bulletPtrPool.at(0);
	}



	//entClass* getBulletFromPool(entStore* entStoreIn) {
	//	entClass* bulletToShootPtr;
	//	bulletToShootPtr = entStoreIn->bulletPtrPool[0]; // todo fixes a heisenbug
	//	// get first inactive bullet
	//	for (entClass* i : entStoreIn->bulletPtrPool) {
	//		bulletToShootPtr = i;
	//		if (!i->isActive) {
	//			bulletToShootPtr = i;
	//			break;
	//		}
	//		return bulletToShootPtr;
	//	}
	//}


	void shoot(Textures* texObj, entStore* entStoreIn, float elapsedTimeSinceLastFrame) {
		if (shootCooldown >= 0.0) {
			shootCooldown -= elapsedTimeSinceLastFrame;
		}
		if ((activeBullets < MAXBULLETS) && (shootCooldown <= 0.0)) {
		//if (activeBullets < MAXBULLETS){//} && (shootCooldown < 0.0)) {
			entClass* firedBulletPtr = getBulletFromPool(entStoreIn);
			firedBulletPtr->isActive = true;
			firedBulletPtr->xPos = xPos;
			firedBulletPtr->yPos = yPos;
			firedBulletPtr->xVel = BULLETSPEED;
			shootCooldown = MAXSHOOTCOOLDOWN;
		}
		else {
			std::cout << shootCooldown;
		}
	}


	void doOtherPlrInput(Textures* texObjIn, entStore* entStoreIn, float elapsedTimeSinceLastFrame) {
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			shoot(texObjIn, entStoreIn, elapsedTimeSinceLastFrame);
		}
	}
};
