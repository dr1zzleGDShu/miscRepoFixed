#include <assert.h>
#include <iostream>
#include <sstream>

//#include "..\..\SFML-2.5.1\include\SFML\Graphics.hpp"
#include "SFML\Graphics.hpp"
#include "Utils.h"
#include "..\..\sqlite\sqlite3.h"


using namespace sf;
using namespace std;


// cpp incl ..\..\..\DirectXTK\Inc


/*
* Doesn't really do anything yet, but a good starter app
* for sfml and sqlite.
*/
int main()
{
	// Create the main window
	RenderWindow window(VideoMode(1200, 800), "database");
	sf::Font font;
	if (!font.loadFromFile("data/fonts/comic.ttf"))
		assert(false);

	DebugPrint("Database starter app");




	Clock clock;
	// Start the game loop 
	while (window.isOpen())
	{
		bool fire = false;
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed) 
				window.close();
		} 

		// Clear screen
		window.clear();

		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::Text txt("Database starter app", font, 30);
		window.draw(txt);


		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
