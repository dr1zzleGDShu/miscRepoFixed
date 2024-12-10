#include <assert.h>
#include <string>

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



int main()
{
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "ship shmup");

	// create an object to store all of our entities, as well as manipulate them en masse
	entStore entStore;

	// create that stores both bg texs and entity texs
	// all additional (non background) texs are stored in within this opject, but within my own datatypes due to the preexisting system being inextendable
	Textures texObj;
	texObj.LoadTextures();

	// create ship
	ship shipEnt;
	shipEnt.initEnt(texObj.madTexArr[TEXSHIP0], 100, 100, 0.2);
	entStore.entVect.push_back(&shipEnt);

	// create a ui object of text, currently only supports comic sans
	// currently this hardcoded uiTxt ptr is the only way to access it 
	madTxt uiTxt;
	uiTxt.initTxt("Parallax Background Demo\nArrow Keys to move",0,0,128,0,0,225);


	// used for delta time between frames, for physics
	Clock clock;


	// Start the game loop 
	while (window.isOpen())
	{
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window if x is pressed
			if (event.type == Event::Closed) 
				window.close();
			if (event.type == Event::TextEntered)
			{
				// close window in esc key is pressed
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close(); 
			}
		} 


		// delta time between frames 
		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();


		// gets player input again within this function
		// possible optimisation, get the user input only once and pass in
		// does not actually move the ship, just changes the velocity/accell of the ship
		shipEnt.doShipMovement(0,0, GC::SCREEN_RES.x, GC::SCREEN_RES.y);

		// Clear screen
		window.clear();

		// draw stuff
		texObj.DrawBgnd(elapsed, window);
		// do physics for all ents in the ent store
		// the ship si act moved here
		entStore.updateEntsPositions(elapsed, 100, GC::SCREEN_RES.x, 0, GC::SCREEN_RES.y-100);
		// draw all ents
		entStore.drawEntStore(window);

		// draw the ui
		window.draw(uiTxt.txt);

		// Update the window
		window.display();

	}

	return EXIT_SUCCESS;
}

