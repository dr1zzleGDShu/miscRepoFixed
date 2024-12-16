#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include "Game.h"



//#####################################
// DEBUG 
// WIN32
//#####################################


const int ASTSIZE = 100;

struct entStore;

struct entClass {
	float xPos, yPos;
	float xVel = 0, yVel = 0;
    float sprOffsetX = 0, sprOffsetY = 0;
    int c = 0; // TODO DEL THIS
    const float maxVel = 600;
    bool scrollingEnt = true;
    //float xSize = 50, ySize = 50;
    float radius = 40; //only supports circle collisions rn so no x/y radius
    bool debugOverlap = false;
    sf::CircleShape debugCircle;
    bool drawDebugCircle = true;
    int lifetime = 0;
    int LIFETIMERESPAWNLIMIT = 4;
    bool isBullet = false;
    bool isAsteroid = false;
    bool isActive = true;
    bool isShip = false;
    float entSizeX = 100;
    float entSizeY = 180;
    float rcsCoeff = 0.998;

    sf::Sprite entSpr;


    void debugPosOut() {
        ++c;
        std::cout << xPos << yPos << ++c;
    }

    void debugVelOut() {
        ++c;
        std::cout << xVel << yVel << ++c;
    }

    void isBulletDebug(int code) {
        if (isBullet && isActive && (10 < code) && (20 > code)) {
            std::cout << "debug: " << code;
        }
    }

    void initDebugCircle(){
        sf::Color col;
        debugCircle.setRadius(radius);
        debugCircle.setPointCount(20);
        if (debugOverlap) { col = sf::Color(250, 0, 0); }
        else { col = sf::Color(0, 250, 0); }
        debugCircle.setOutlineColor(col);
        debugCircle.setOutlineThickness(2);
        debugCircle.setFillColor(sf::Color::Transparent);
        debugCircle.setPosition(xPos, yPos);
    }

    void updateDebugCircle() {
        sf::Color col;
        if (debugOverlap) { col = sf::Color(250, 0, 0); }
        else { col = sf::Color(0, 250, 0); }
        debugCircle.setOutlineColor(col);
        debugCircle.setPosition(xPos, yPos);
    }

    void initEnt(sf::Texture& entTexIn, int xPosIn, int yPosIn, float scaleIn) {
        xPos = xPosIn; yPos = yPosIn;
        entSpr.setTexture(entTexIn);
        entSpr.setScale(scaleIn, scaleIn);
        initDebugCircle();
    }

    void rotSpr(int degIn){
        entSpr.setRotation(degIn);
    }

    void renderEnt(sf::RenderWindow& winIn) {
        entSpr.setPosition(xPos+ sprOffsetX, yPos+sprOffsetY);
        winIn.draw(entSpr);
        if (drawDebugCircle) {
            updateDebugCircle();
            winIn.draw(debugCircle);
        }
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
        
        if (isShip) {
            xVel *= rcsCoeff;
            yVel *= rcsCoeff;

        }
    }

    void mvEnt(float elapsedTimeSinceLastFrame, float xDisplace, float yDisplace, int xBoundMin, int xBoundMax, int yBoundMin, int yBoundMax, entStore* entStorePtr) {
        // cant move outside of x/y bounds
        xPos += xDisplace*elapsedTimeSinceLastFrame;
        yPos += yDisplace*elapsedTimeSinceLastFrame;

        if (scrollingEnt && (xPos < xBoundMin)) {
            respawnEntOffscreen(xBoundMax, yBoundMax, entStorePtr);
        }

        if (isBullet && (xPos > xBoundMax)) {
            isActive = false;
        }

        // clamp the value to bounds (converted from ints to floats (bcs of screen size being an int))
        if (isShip) {
            xPos = std::max(static_cast<float>(xBoundMin+entSizeX), std::min(xPos, static_cast<float>(xBoundMax - entSizeX)));
        }
        yPos = std::max(static_cast<float>(yBoundMin), std::min(yPos, static_cast<float>(yBoundMax - entSizeY)));
    }

    void updateEntPos(float, int, int, int, int, entStore*);

    void respawnEntOffscreen(int , int , entStore* );

    bool checkCircleColEntWrapper(entClass* entToCheck) {
        // true if overlapping
        float thisEntCenterPosX = (xPos)+radius;
        float thisEntCenterPosY = (yPos) + radius;
        float entToCheckCenterPosX = (entToCheck->xPos) + entToCheck->radius;
        float entToCheckCenterPosY = (entToCheck->yPos) + entToCheck->radius;
        float minDist = radius + entToCheck->radius;

        return checkCircleColRaw(minDist, thisEntCenterPosX, thisEntCenterPosY, entToCheckCenterPosX, entToCheckCenterPosY);
    }

    bool checkCircleColValWrapper(float foreignXPosOrigin, float foreignYPosOrigin, float foreignRadius) {
        // true if overlapping
        float thisEntCenterPosX = (xPos)+radius;
        float thisEntCenterPosY = (yPos)+radius;
        float entToCheckCenterPosX = foreignXPosOrigin + foreignRadius;
        float entToCheckCenterPosY = foreignYPosOrigin + foreignRadius;
        float minDist = foreignRadius + radius;

        return checkCircleColRaw(minDist, thisEntCenterPosX, thisEntCenterPosY, entToCheckCenterPosX, entToCheckCenterPosY);
    }



    bool checkCircleColRaw(int minDistIn, float objACntrPosXIn, float objACntrPosYIn, float objBCntrPosXIn, float objBCntrPosYIn) {
        float dist = (objACntrPosXIn - objBCntrPosXIn) * (objACntrPosXIn - objBCntrPosXIn) + (objACntrPosYIn - objBCntrPosYIn) * (objACntrPosYIn - objBCntrPosYIn);
        dist = sqrtf(dist);
        return dist <= minDistIn;
    }
};


