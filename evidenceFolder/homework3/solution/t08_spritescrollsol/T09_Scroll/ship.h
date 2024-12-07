#pragma once

#include <assert.h>


#include "entity.h"

using namespace sf;
using namespace std;

struct ship : public entClass {
	const float SHIPACCELL = 0.15f;

	void doShipMovement(int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
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
		cout << inputDirect[0] << inputDirect[1] << endl;

		accelEnt(inputDirect[0] * SHIPACCELL, inputDirect[1] * SHIPACCELL);
		//accelEnt(inputDirect[0] * SHIPSPEED * 1, inputDirect[1] * SHIPSPEED * 1);

		//setPos(100, 300);

	}

};
