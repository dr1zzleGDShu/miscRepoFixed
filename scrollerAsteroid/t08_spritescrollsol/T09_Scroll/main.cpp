#include <assert.h>
#include <string>

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "main.h"
#include "entity.h"

using namespace sf;
using namespace std;


/**
########################################
## COMPILE WITH:
##   DEBUG
##   WIN32
########################################
**/



int main()
{

	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "ship shmup");

	entStore entStore;

	// create bg texs
	Textures texObj;
	texObj.LoadTextures();

	// create ship
	entClass shipEnt;
	shipEnt.initEnt(texObj.madTexArr[TEXSHIP0], 100, 100, 0.2);
	entStore.entVect.push_back(shipEnt);
	shipEnt.xVel = 5;


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

		// Clear screen
		window.clear();

		texObj.DrawBgnd(elapsed, window);
		entStore.drawEntStore(window);
		entStore.updateEntsPositions(0, GC::SCREEN_RES.x, 0, GC::SCREEN_RES.y);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}

