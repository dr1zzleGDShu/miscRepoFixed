#include "ship.h"
#include "entStore.h"


void ship::doShipMovement() {
	// changes the velocity values ship based on arrow keys
	// does not actually move the ship (see updateEntsPositions in entStore)
	int inputDirect[2] = { 0,0 };

	// get inputted direction
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

	// change the velocity values of the ship
	accelEnt(inputDirect[0] * SHIPACCELL, inputDirect[1] * SHIPACCELL);
}


entClass* ship::getBulletFromPool(entStore* entStoreIn) {
	// instead of spawning and destroying bullets, they are all pooled and when required will pick and inative one
	// gets first inactive bullet from pool
	for (int i = 0; i < MAXBULLETS; i++) {
		if (!(entStoreIn->bulletPtrPool.at(i)->isActive)) {
			return entStoreIn->bulletPtrPool.at(i);
		}
	}
	// just in case player has managed to shoot all 50 bullets
	return entStoreIn->bulletPtrPool.at(0);
}


void ship::shoot(Textures* texObj, entStore* entStoreIn, float elapsedTimeSinceLastFrame) {
	if (shootCooldown >= 0.0) {
		shootCooldown -= elapsedTimeSinceLastFrame;
	}
	if ((activeBullets < MAXBULLETS) && (shootCooldown <= 0.0)) {
		//if (activeBullets < MAXBULLETS){//} && (shootCooldown < 0.0)) {
		entClass* firedBulletPtr = getBulletFromPool(entStoreIn);
		firedBulletPtr->isActive = true;
		firedBulletPtr->xPos = xPos + BULLETOFFSETX;
		firedBulletPtr->yPos = yPos + BULLETOFFSETY;
		firedBulletPtr->xVel = BULLETSPEED;
		shootCooldown = MAXSHOOTCOOLDOWN;
	}
	else {
		std::cout << shootCooldown;
	}
}


void ship::doOtherPlrInput(Textures* texObjIn, entStore* entStoreIn, float elapsedTimeSinceLastFrame) {
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		shoot(texObjIn, entStoreIn, elapsedTimeSinceLastFrame);
	}
}