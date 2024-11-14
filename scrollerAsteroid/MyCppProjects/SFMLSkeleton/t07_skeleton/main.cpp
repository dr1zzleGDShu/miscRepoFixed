#include <assert.h>

#include "SFML/Graphics.hpp"


using namespace sf;

//dimensions in 2D that are whole numbers
struct Dim2Di
{
	int x, y;
};

//dimensions in 2D that are floating point numbers
struct Dim2Df
{
	float x, y;
};


/*
A box to put Games Constants in.
These are special numbers with important meanings (screen width,
ascii code for the escape key, number of lives a player starts with,
the name of the title screen music track, etc.
*/
namespace GC
{
	//game play related constants to tweak
	const Dim2Di SCREEN_RES{ 1200,800 };

	const char ESCAPE_KEY{ 27 };
}



int main()
{
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "My first code");

	// Load a sprite to display
	Texture texture;
	if (!texture.loadFromFile("data/2dsprite.png"))
		assert(false);


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

		// Clear screen
		window.clear();

		//instantiate and draw a sprite
		Sprite spr(texture);
		window.draw(spr);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
