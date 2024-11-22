#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>


//#####################################
// DEBUG 
// WIN32
//#####################################

struct entClass {
	float xPos, yPos;
	float xVel, yVel;
    const float maxVel = 20;
    const float accel = 4;

    sf::Sprite entSpr;

    void initEnt(sf::Texture& entTexIn, int xPosIn, int yPosIn, float scaleIn) {
        xPos = xPosIn; yPos = yPosIn;
        entSpr.setTexture(entTexIn);
        entSpr.setScale(scaleIn, scaleIn);
    }

    void renderEnt(sf::RenderWindow& winIn) {
        entSpr.setPosition(xPos, yPos);
        winIn.draw(entSpr);
    }

    void setPos(float xPosIn, float yPosIn) {
        xPos = xPosIn; yPos = yPosIn;
    }

    void accelEnt(float xAccelIn, float yAccelIn) {
        xVel += xAccelIn;
        yVel += yAccelIn;

        //clamp the value
        xVel = std::max(-maxVel, std::min(xVel, maxVel));
        yVel = std::max(-maxVel, std::min(yVel, maxVel));
    }

    void mvEnt(float xDisplace, float yDisplace, int xBoundMin, int xBoundMax, int yBoundMin, int yBoundMax ) {
        // cant move outside of x/y bounds
        xPos += xDisplace;
        yPos += yDisplace;

        // clamp the value to bounds (converted from ints to floats (bcs of screen size being an int))
        xPos = std::max(static_cast<float>(xBoundMin), std::min(xPos, static_cast<float>(xBoundMax)));
        yPos = std::max(static_cast<float>(xBoundMin), std::min(yPos, static_cast<float>(xBoundMax)));

    }

    void updateEntPos(int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
        // auto update entPos using current velocity
        // assumes velocity is already updated

        mvEnt(xVel, yVel, xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn);

    }
};


struct entStore {

    std::vector<entClass> entVect = {};

    void drawEntStore(sf::RenderWindow& winIn) {
        for (entClass i : entVect) {
            i.renderEnt(winIn);
        }
    }

    void updateEntsPositions(int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
        for (entClass i : entVect) {
            i.updateEntPos(xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn);
        }

    }
};