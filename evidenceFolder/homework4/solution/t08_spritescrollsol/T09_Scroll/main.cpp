#include <assert.h>
#include <string>
#include <cstdlib>


#include "SFML/Graphics.hpp"
#include "Game.h"
#include "main.h"
#include "entity.h"
#include "ship.h"
#include "entStore.h"

using namespace sf;
using namespace std;


/**
########################################
## COMPILE WITH:
##   DEBUG
##   WIN32
########################################
**/


void makeBullet(Textures* texObj, entStore* entStoreIn) {
	entClass bulletEnt;
	bulletEnt.isBullet = true;
	bulletEnt.isActive = GC::TESTINGMAXBULLETCOUNT;
	bulletEnt.radius = 15;// TODO magic numbers
	bulletEnt.initEnt(texObj->madTexArr[TEXBULLET0], 0, 0, 0.5);
	entStoreIn->entVect.push_back(bulletEnt);
	entStoreIn->bulletPtrPool.push_back(&(entStoreIn->entVect.back()));
}


void makeAsteroid(Textures* texObj, entStore* entStoreIn) {
	entClass asteroidEnt;
	asteroidEnt.initEnt(texObj->getRandomAsterTex(), rand() % GC::SCREEN_RES.x - ASTSIZE, rand() % GC::SCREEN_RES.y - ASTSIZE, 1);
	asteroidEnt.xVel = -100;
	asteroidEnt.isAsteroid = true;
	entStoreIn->entVect.push_back(asteroidEnt);
}



void entClass::updateEntPos(float elapsedTimeSinceLastFrame, int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn, entStore* entStorePtr) {
	// simpily moves xPos and yPos based on 
	// auto update entPos using current velocity
	// assumes velocity is already updated
	mvEnt(elapsedTimeSinceLastFrame, xVel, yVel, xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn, entStorePtr);
}


void entClass::respawnEntOffscreen(int xBoundMaxIn, int yBoundMaxIn, entStore* entStorePtr) {
	// TODO rewite this func with new lifetime system in mind
	lifetime = 0;
	setPos((float)(xBoundMaxIn + (rand() % 300)), (float)(rand() % (yBoundMaxIn - ASTSIZE)));
}


entClass* ship::getBulletFromPool(entStore* entStoreIn) {
	// for loops only work when there is a breakpoint in the fuction, for some reason 
	for (int i = 0; i < MAXBULLETS; i++) {
		if (!(entStoreIn->bulletPtrPool.at(i)->isActive)) {
			/*if (i == 10) {
				std::cout << "make this line a breakpoint";
			*///}
			return entStoreIn->bulletPtrPool.at(i);
		}
	}
	return entStoreIn->bulletPtrPool.at(0);
}


void entStore::updateDebugOverlap(entClass* entIn) {
	entIn->debugOverlap = false;
	for (entClass& i : entVect) {
		if (i.isActive){
			if (i.checkCircleColEntWrapper(entIn)) {
				if (&i != entIn) {
					entIn->debugOverlap = true;
					if ((i.lifetime < i.LIFETIMERESPAWNLIMIT) && i.isAsteroid) {
						i.respawnEntOffscreen(GC::SCREEN_RES.x, GC::SCREEN_RES.y, this);
						entIn->debugOverlap = false;
					}
					if (i.isBullet && entIn->isAsteroid) {
						entIn->respawnEntOffscreen(GC::SCREEN_RES.x, GC::SCREEN_RES.y, this);
						entIn->debugOverlap = false;
						i.isActive = false;
					}
					if (entIn->isShip && !i.isBullet && entIn->lifetime>GC::SHIPSPAWNINVULN) {
						entIn->isActive = false; // TODO FAIL STATE 
					}
				}
			}
		}
	}
}


int main()
{

	// seed the random
	std::srand(std::time(nullptr)); 


	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "ship shmup");

	// create the object that stores all out entitys 
	entStore entStore;
	entStore.entVect.reserve(1024);

	// create bg texs
	Textures texObj;
	texObj.LoadTextures();


	// TODO move ship ent to function mby, didnt work before idk why
	// create the ship object, extends entity object 
	ship shipEnt;
	shipEnt.rotSpr(90);
	shipEnt.xVel = 5;
	shipEnt.scrollingEnt = false;
	shipEnt.isShip = true;
	shipEnt.sprOffsetX = 100;
	shipEnt.sprOffsetY = -10;
	shipEnt.radius = 40;
	shipEnt.initEnt(texObj.madTexArr[TEXSHIP0], 100, 100, 0.2);
	//entStore.entVect.push_back(shipEnt);
	entStore.shipPtr = &shipEnt;
	
	entStore.bulletPtrPool.reserve(shipEnt.MAXBULLETS);
	for (int i = 0; i < shipEnt.MAXBULLETS; i++) {
		makeBullet(&texObj, &entStore);
	}

	vector<entClass> asteroidsVect = {};
	for (int i = 0; i < 24; ++i) {
		makeAsteroid(&texObj, &entStore);
	}
	
	// redundant 
	//entStore.wiggleAstroidsAtSpawn(GC::SCREEN_RES.x, GC::SCREEN_RES.y);


	entStore.createEntPtrsVect();


	Clock clock;

	// Start the game loop 
	while (window.isOpen())
	{
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed) 
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close(); 
			}
		} 

		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();

		shipEnt.doShipMovement(0,0, GC::SCREEN_RES.x, GC::SCREEN_RES.y);

		shipEnt.doOtherPlrInput(&texObj, &entStore, elapsed);
		//shipEnt.shoot(&texObj, &entStore);
		
		// Clear screen
		window.clear();

		texObj.DrawBgnd(elapsed, window);

		entStore.updateEntsPositions(elapsed, 100, GC::SCREEN_RES.x, 0, GC::SCREEN_RES.y-100);

		entStore.drawEntStore(window);

		// Update the window
		window.display();

	}

	return EXIT_SUCCESS;
}

