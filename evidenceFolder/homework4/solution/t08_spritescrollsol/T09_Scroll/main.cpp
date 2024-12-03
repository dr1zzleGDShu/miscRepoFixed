#include <assert.h>
#include <string>
#include <cstdlib>


#include "SFML/Graphics.hpp"
#include "Game.h"
#include "main.h"
#include "entity.h"
#include "ship.h"

using namespace sf;
using namespace std;


/**
########################################
## COMPILE WITH:
##   DEBUG
##   WIN32
########################################
**/


void makeAsteroid(Textures* texObj, entStore* entStoreIn) {
	entClass asteroidEnt;
	asteroidEnt.initEnt(texObj->getRandomAsterTex(), rand() % GC::SCREEN_RES.x - ASTSIZE, rand() % GC::SCREEN_RES.y - ASTSIZE, 1);
	asteroidEnt.xVel = -100;
	entStoreIn->entVect.push_back(asteroidEnt);
}


int main()
{
	std::srand(std::time(nullptr)); 


	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "ship shmup");

	entStore entStore;

	// create bg texs
	Textures texObj;
	texObj.LoadTextures();

	//int shipIndex = createShip(&texObj, &entStore);

	ship shipEnt;
	shipEnt.initEnt(texObj.madTexArr[TEXSHIP0], 100, 100, 0.2);
	shipEnt.rotSpr(90);
	shipEnt.xVel = 5;
	shipEnt.scrollingEnt = false;

	entStore.shipPtr = &shipEnt;


	vector<entClass> asteroidsVect = {};
	for (int i = 0; i < 24; ++i) {
		makeAsteroid(&texObj, &entStore);
	}

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

