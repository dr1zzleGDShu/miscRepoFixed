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

	int score = 0;

	entStore entStore;

	// create bg texs
	Textures texObj;
	texObj.LoadTextures();

	// create ship
	ship shipEnt;
	shipEnt.initEnt(texObj.madTexArr[TEXSHIP0], 100, 100, 0.2);
	entStore.entVect.push_back(&shipEnt);
	shipEnt.xVel = 5;

	sf::Font font;
	if (!font.loadFromFile("data/fonts/comic.ttf"))
		assert(false);


	sf::Text txt("Scrolling Parallax demo\nArrow keys to move", font, 30);
	txt.setPosition(10, 10);
	sf::Color fgColor(0, 0, 128);
	sf::Color bgColor(0, 0, 255);
	txt.setFillColor(fgColor);
	txt.setOutlineColor(bgColor);





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

		// draw stuff
		texObj.DrawBgnd(elapsed, window);
		entStore.updateEntsPositions(elapsed, 100, GC::SCREEN_RES.x, 0, GC::SCREEN_RES.y-100);
		entStore.drawEntStore(window);

		window.draw(txt);

		// Update the window
		window.display();

		++score;
	}

	return EXIT_SUCCESS;
}

