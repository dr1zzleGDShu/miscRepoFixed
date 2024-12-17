#include <string>
#include <assert.h>
#include <sstream>
#include <map>
#include <tuple>

#include "Game.h"

using namespace std;
using namespace sf;

// i have many issues with the other one, basically only works for 8 tex with the current imp, no much effort to fix it to get it working with ship tex
//map<const char*, sf::Texture> madTexArr[16]; // update size
//tuple<string, const char*> madTexPaths[] = { {"ship","data/ship.png"} }; // didnt work when was a 2d arr of const char*, prob me messing up the dereference


void Textures::LoadTextures()
{
	// bg texs
	stringstream ss;
	//for (int i = 0; i < MAX_TEXTURES; ++i)     << orig line that was replaced
	for (int i = 0; i < 8; ++i) // 8 = num of backround texs, if i add stuff to the tex map and use MAX_TEXTURES then it breaks (why it build like this >:| )
		// Currently only works on the first 8 tex in the map  
		// TODO fix this if u can be bothered, or redo all the text map cause it shit outside of very narrow orig use case
	{
		ss.str("");
		ss << "data/backgroundLayers/mountains01_00" << i << ".png";

		Texture& t = Get(static_cast<Tex>(i));

		if (!t.loadFromFile(ss.str()))
			assert(false);
		t.setRepeated(true);
	}


	// non background textures
	populateMadTexPaths();

	int c = 0;
	for (string j : madTexPaths) {
		// load all textures in the tex paths arr
		sf::Texture myTex;
		cout << j;
		if (!myTex.loadFromFile(j)) {
			assert(false);
		}
		madTexArr[c] = myTex;
		c++;

	}
}

void Textures::ScrollBgnd(Tex texId, sf::RenderWindow & window, int inc)
{
	sf::Sprite spr(Get(texId));
	sf::IntRect scroll = spr.getTextureRect();
	scroll.left += inc;
	spr.setTextureRect(scroll);
	spr.setScale(window.getSize().x / (float)scroll.width, window.getSize().y / (float)scroll.height);
	spr.setPosition(0, 0);
	window.draw(spr);
}


void Textures::DrawBgnd(float elapsed, sf::RenderWindow &window)
{
	//background order of sprites


	float spd = GC::BACK_SPEED * elapsed;
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		bgndSpds[i] += spd;
		ScrollBgnd(ids[i], window, (int)bgndSpds[i]);
		spd += GC::BACK_LAYER_SPEEDINC * elapsed;
	}
}

void Textures::populateMadTexPaths() {
	madTexPaths[0] = string("data/ship0.png"); // hardcoded paths to ship and bullet
	madTexPaths[1] = string("data/bullet0.png"); // TODO remove hardcoded paths
	for (int i = 0; i < NUMOFASTERTEX; i++) {
		string madPath = "data/asteroidSprs/";
		madPath += to_string(i);
		madPath += ".png";
		madTexPaths[i+ PREASTERTEXAMOUNT] = madPath;
	}
}
