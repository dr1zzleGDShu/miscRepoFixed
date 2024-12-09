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
    //float xSize = 50, ySize = 50;
    float size = 50; //only supports circle collisions rn so no x/y size

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

    bool checkCircleCol(entClass* entToCheck) {
        // true if overlapping
        float thisEntCenterPosX = (xPos)+size;
        float thisEntCenterPosY = (yPos) + size;
        float entToCheckCenterPosX = (entToCheck->xPos) + entToCheck->size;
        float entToCheckCenterPosY = (entToCheck->yPos) + entToCheck->size;
        float minDist = size + entToCheck->size;

        float dist = (thisEntCenterPosX - entToCheckCenterPosX) * (thisEntCenterPosX - entToCheckCenterPosX) + (thisEntCenterPosY - entToCheckCenterPosY) * (thisEntCenterPosY - entToCheckCenterPosY);
        dist = sqrtf(dist);
        return dist <= minDist;
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

    entClass* checkShipCollidingWithAsteroids(bool* noneTouchingIn) {
        for (entClass& i : entVect) {
            if (i.checkCircleCol(shipPtr)) {
                noneTouchingIn = false;
                return &i;
            }
        }
    }


    entClass* getFirstOverlappingAsteroidWithAsteroid(bool* noneTouchingIn) {
        for (entClass& i : entVect) {
            for (entClass& j : entVect) {
                if ((i.xPos != j.xPos) && (i.yPos != j.yPos)) { // todo act check if they are the same obj, this will cause errors if they are 2 objs in the same place
                    if (i.checkCircleCol(&j)) {
                        noneTouchingIn = false;
                        return &i;
                    }
                }
            }
        }
    }


    void wiggleAstroidsAtSpawn(int xBoundMaxIn, int yBoundMaxIn) {
        bool noneTouching = false;
        while (!noneTouching) {
            noneTouching = true;
            checkShipCollidingWithAsteroids(&noneTouching)->respawnEntOffscreen(xBoundMaxIn, yBoundMaxIn);
            getFirstOverlappingAsteroidWithAsteroid(&noneTouching)->respawnEntOffscreen(xBoundMaxIn, yBoundMaxIn);
            std::cout << noneTouching;
        }
    }


    bool checkAstroidCollisionsToPos() {
        bool toRet = false;

    }
};