#include <assert.h>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

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
	srand(time(0));
	int directDownCoeff = 1;
	int directRightCoeff = 1;
	float speed = 0.05f;
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "My first code");

	// Load a sprite to display
	Texture texture;
	if (!texture.loadFromFile("data/2dsprite.png"))
		assert(false);

	float rot = 0.0f;
	float posVec[2] = { 600.0f,400.0f };
	float sprSize = 150;
	float downLimit = 800 - sprSize;
	float rightLimit = 1200 - sprSize;
	bool modColorQueue = false;
	int imgColour[3] = { 255,255,255 };


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
		spr.setScale(0.3f, 0.3f);
		//spr.setRotation(rot);
		//rot += 0.005f;
		spr.setPosition(posVec[0], posVec[1]);
		posVec[0] += speed * directRightCoeff;
		posVec[1] += speed * directDownCoeff;
		
		modColorQueue = false;

		
		if (posVec[0] >= rightLimit) { directRightCoeff = -1; modColorQueue = true; };
		if (posVec[1] >= downLimit) { directDownCoeff = -1; modColorQueue = true; };
		if (posVec[0] <= 0) { directRightCoeff = 1; modColorQueue = true; };
		if (posVec[1] <= 0) { directDownCoeff = 1; modColorQueue = true; };

		if (modColorQueue){
			imgColour[0] = rand() % 255;
			imgColour[1] = rand() % 255;
			imgColour[2] = rand() % 255;
		}
		spr.setColor(sf::Color(imgColour[0], imgColour[1], imgColour[2]));


		//posVec[0] += ;
		window.draw(spr);
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
