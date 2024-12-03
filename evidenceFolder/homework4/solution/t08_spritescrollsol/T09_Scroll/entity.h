#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>



//#####################################
// DEBUG 
// WIN32
//#####################################


const int ASTSIZE = 0;

struct entClass {
	float xPos, yPos;
	float xVel = 0, yVel = 0;
    int c = 0; // TODO DEL THIS
    const float maxVel = 400;
    bool scrollingEnt = true;

    sf::Sprite entSpr;


    void debugPosOut() {
        ++c;
        std::cout << xPos << yPos << ++c;
    }

    void debugVelOut() {
        ++c;
        std::cout << xVel << yVel << ++c;
    }

    void initEnt(sf::Texture& entTexIn, int xPosIn, int yPosIn, float scaleIn) {
        xPos = xPosIn; yPos = yPosIn;
        entSpr.setTexture(entTexIn);
        entSpr.setScale(scaleIn, scaleIn);
    }

    void rotSpr(int degIn){
        entSpr.setRotation(degIn);
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

    void mvEnt(float elapsedTimeSinceLastFrame, float xDisplace, float yDisplace, int xBoundMin, int xBoundMax, int yBoundMin, int yBoundMax ) {
        // cant move outside of x/y bounds
        xPos += xDisplace*elapsedTimeSinceLastFrame;
        yPos += yDisplace*elapsedTimeSinceLastFrame;

        if (scrollingEnt && (xPos < xBoundMin)) {
            respawnEntOffscreen(xBoundMax, yBoundMax);
        }

        // clamp the value to bounds (converted from ints to floats (bcs of screen size being an int))
        xPos = std::max(static_cast<float>(xBoundMin), std::min(xPos, static_cast<float>(xBoundMax)));
        yPos = std::max(static_cast<float>(yBoundMin), std::min(yPos, static_cast<float>(yBoundMax)));
    }

    void updateEntPos(float elapsedTimeSinceLastFrame, int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
        // auto update entPos using current velocity
        // assumes velocity is already updated

        // TODO why is yVel so big
        mvEnt(elapsedTimeSinceLastFrame, xVel, yVel, xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn);
    }

    void respawnEntOffscreen(int xBoundMaxIn, int yBoundMaxIn) {
        int xVal = xBoundMaxIn+rand()%300;
        int yVal = rand() % (yBoundMaxIn - ASTSIZE);

        setPos((float)xVal, (float)yVal);

    }
};


struct entStore {

    //std::vector<entClass*> entVect = {};
    std::vector<entClass> entVect = {};
    entClass* shipPtr; // cant store it as a ship due to circualar depedency, need to split this obj into a diff file if thats needed


    void drawEntStore(sf::RenderWindow& winIn) {
        shipPtr->renderEnt(winIn);
        for (entClass i : entVect) {
            i.renderEnt(winIn);
        }
    }

    void updateEntsPositions(float elapsedTimeSinceLastFrame, int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
        shipPtr->updateEntPos(elapsedTimeSinceLastFrame, xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn);
        for (entClass &i : entVect) {
            i.updateEntPos(elapsedTimeSinceLastFrame, xBoundMinIn-200, xBoundMaxIn, yBoundMinIn, yBoundMaxIn+200);
        }
    }
};