#pragma once

#include <vector>
#include <cstdlib>

#include "SFML/Graphics.hpp"

#include "entity.h"


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

enum madTexLookup { PREASTERTEXAMOUNT = 2, TEXSHIP0 = 0, TEXBULLET0 = 1};
 
//all the textures we need
struct Textures
{
	const int NUMOFASTERTEX = 64;
	sf::Texture madTexArr[128]; // update size


	// TODO remove magic num
	// PREASTERTEXAMOUNT+NUMOFASTERTEX
	std::string madTexPaths[66];// = { "data/ship.png" }; 
	

	//give each texture an ID
	typedef enum {
		BACK0 = 0, //large backdrop sprites
		BACK1 = 1,
		BACK2 = 2,
		BACK3 = 3,
		BACK4 = 4,
		BACK5 = 5, 
		BACK6 = 6,
		BACK7 = 7,
	} Tex;
	static const int MAX_TEXTURES = 8; // orig 8
	sf::Texture tex[MAX_TEXTURES];
	
	Textures::Tex ids[MAX_TEXTURES]{
		Textures::BACK7,
		Textures::BACK5,
		Textures::BACK4,
		Textures::BACK3,
		Textures::BACK2,
		Textures::BACK1,
		Textures::BACK0,
		Textures::BACK6,
	};//a variable to hold each texture
	float bgndSpds[MAX_TEXTURES] = { 0,0,0,0,0,0,0,0 };	//keep track of the scroll position of each bgnd layer

	//given a texture ID, get the actual texture
	sf::Texture& Get(Tex id) {
		return tex[static_cast<int>(id)];
	}

	/*
	LoadTextures- load all textures
	precon		- no textures loaded
	postcon		- all textures loaded
	*/
	void LoadTextures();

	/*
	ScrollBgnd	- scroll a texture as a screen background
	window		- rendering handle
	inc			- how fast to scroll
	precon		- the texture is set to repeat and inc is a time adjusted smooth value
				- note that the increment cannot be float
	postcon		- teh textures scrolls based on vlaue of inc
	*/
	void ScrollBgnd(Tex texId, sf::RenderWindow& window, int inc);

	/*
	DrawBgnd	- draw all background layers
	elased		- time in secs since last call to this function
	window		- for drawing
	precon		- window and textures are ready
	postcon		- all 7 layers of the background drawn full screen
				  and each one scrolling at a different speed
	*/
	void DrawBgnd(float elapsed, sf::RenderWindow &window);


	void populateMadTexPaths();


	sf::Texture& getRandomAsterTex() {
		return madTexArr[PREASTERTEXAMOUNT+(rand()%NUMOFASTERTEX)];
	}
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
	const Dim2Di SCREEN_RES{ 1024,512 };
	//background
	const float BACK_SPEED = 10;		//start speed for scrolling
	const float BACK_LAYER_SPEEDINC = 7;//each layer is a bit faster towards the front

	const char ESCAPE_KEY{ 27 };
}

