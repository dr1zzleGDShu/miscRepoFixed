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
	//void makeAsteroid(vector<entClass>* asteroidsVect, Textures* texObj, entStore* entStoreIn) {
	/*
	entClass asteroidEnt;
	asteroidsVect->push_back(asteroidEnt);
	entClass* tempAsteroidPtr = &asteroidsVect->back();
	//tempAsteroidPtr->initEnt(texObj->madTexArr[TEXASTEROID0], rand() % 1000, rand() % 700, 1);
	tempAsteroidPtr->initEnt(texObj->madTexArr[TEXASTEROID0], 300, 300, 1);
	entStoreIn->entVect.push_back(tempAsteroidPtr);
	tempAsteroidPtr->xVel = -100;
	*/

	/*
	entClass asteroidEnt;
	cout << entStoreIn->entVect.back();
	asteroidEnt.initEnt(texObj->madTexArr[TEXASTEROID0], 300, 300, 1);
	cout << entStoreIn->entVect.back();
	asteroidEnt.xVel = -100;
	cout << entStoreIn->entVect.back();
	asteroidsVect->push_back(asteroidEnt); // <<<<<<<<<<<<<<< THIS FUCKING LINE
	cout << entStoreIn->entVect.back();
	entStoreIn->entVect.push_back(&asteroidsVect->back());
	cout << entStoreIn->entVect.back();
	*/

	entClass asteroidEnt;
	asteroidEnt.initEnt(texObj->madTexArr[TEXASTEROID0], rand() % 1000, rand() % 500, 1);
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
	shipEnt.xVel = 5;

	entStore.shipPtr = &shipEnt;


	vector<entClass> asteroidsVect = {};
	for (int i = 0; i < 10; ++i) {
		makeAsteroid(&texObj, &entStore);
	}
	for (entClass i : asteroidsVect) {
		i.debugPosOut();
	}
	for (entClass i : entStore.entVect) {
		i.debugPosOut();
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
		for (entClass i : entStore.entVect) {
			i.debugPosOut();
		}
		entStore.drawEntStore(window);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}

