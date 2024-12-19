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
	bulletEnt.radius = 15;
	bulletEnt.entSizeX = 40;
	bulletEnt.entSizeY = 40;
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



void createShip(ship* shipEnt, Textures* texObj) {
	shipEnt->rotSpr(90);
	shipEnt->xVel = 5;
	shipEnt->scrollingEnt = false;
	shipEnt->isShip = true;
	shipEnt->sprOffsetX = 100;
	shipEnt->sprOffsetY = -10;
	shipEnt->radius = 40;
	shipEnt->initEnt(texObj->madTexArr[TEXSHIP0], 100, 100, 0.2);
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

	// create the ship object, extends entity object 
	ship shipEnt;
	createShip(&shipEnt, &texObj);
	entStore.shipPtr = &shipEnt;
	
	// make bullets
	entStore.bulletPtrPool.reserve(shipEnt.MAXBULLETS);
	for (int i = 0; i < shipEnt.MAXBULLETS; i++) {
		makeBullet(&texObj, &entStore);
	}

	// make asteroids
	vector<entClass> asteroidsVect = {};
	for (int i = 0; i < 24; ++i) {
		makeAsteroid(&texObj, &entStore);
	}
	
	// create a vector of all entity pointers in entStore
	entStore.createEntPtrsVect();

	// death msg text
	madTxt deathTxt;
	deathTxt.initTxt("      You Died\nPress Esc to Exit", 200, 0, 0, 225, 0, 0);
	deathTxt.txt.setPosition(260, 140);
	deathTxt.txt.setScale(2, 2);


	Clock clock;

	// Start the game loop 
	while (window.isOpen())
	{
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window when x pressed
			if (event.type == Event::Closed) 
				window.close();
			if (event.type == Event::TextEntered)
			{
				// close window on esc pressed
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close(); 
			}
		} 

		// delta time between each frame
		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();

		// if not dead
		if (shipEnt.isActive) {
			// ship movement
			shipEnt.doShipMovement();
			// shooting 
			shipEnt.doOtherPlrInput(&texObj, &entStore, elapsed);
		}
		
		// Clear screen
		window.clear();

		// draw scrolling background
		texObj.DrawBgnd(elapsed, window);

		// move all ents based on there velocity
		entStore.updateEntsPositions(elapsed, 100, GC::SCREEN_RES.x, 0, GC::SCREEN_RES.y-100);

		// draw all ents
		entStore.drawEntStore(window);

		// if dead 
		if (!shipEnt.isActive){
			// draw death text
			window.draw(deathTxt.txt);
		}

		// Update the window
		window.display();

	}

	return EXIT_SUCCESS;
}

