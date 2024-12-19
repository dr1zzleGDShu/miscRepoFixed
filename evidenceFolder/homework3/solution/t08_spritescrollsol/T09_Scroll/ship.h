#pragma once

#include <assert.h>


#include "entity.h"

using namespace sf;
using namespace std;

struct ship : public entClass {
	const float SHIPACCELL = 0.25f;

	void doShipMovement(int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
		// simpily gets user input and changes the velocity of ship ent according
		// does not actually do ship movement

		// where inputted direction is stored/calucated in the function
		int inputDirect[2] = {0,0};


		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			inputDirect[1] -= 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			inputDirect[1] += 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			inputDirect[0] -= 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			inputDirect[0] += 1;
		}

		// used for debug
		cout << inputDirect[0] << inputDirect[1] << endl;

		// modify the ships velocity (definded in the ent class)
		accelEnt(inputDirect[0] * SHIPACCELL, inputDirect[1] * SHIPACCELL);
	}

};
