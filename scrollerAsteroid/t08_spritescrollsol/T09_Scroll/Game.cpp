#include <string>
#include <assert.h>
#include <sstream>

#include "Game.h"

using namespace std;
using namespace sf;

void Textures::LoadTextures()
{
	stringstream ss;
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		ss.str("");
		ss << "data/backgroundLayers/mountains01_00" << i << ".png";

		Texture& t = Get(static_cast<Tex>(i));

		if (!t.loadFromFile(ss.str()))
			assert(false);
		t.setRepeated(true);
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
	Textures::Tex ids[MAX_TEXTURES]{
		Textures::BACK7,
		Textures::BACK5,
		Textures::BACK4,
		Textures::BACK3,
		Textures::BACK2,
		Textures::BACK1,
		Textures::BACK0,
		Textures::BACK6,
	};

	float spd = GC::BACK_SPEED * elapsed;
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		bgndSpds[i] += spd;
		ScrollBgnd(ids[i], window, (int)bgndSpds[i]);
		spd += GC::BACK_LAYER_SPEEDINC * elapsed;
	}
}
