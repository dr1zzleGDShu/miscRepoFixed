#include "entity.h"
#include "entStore.h"
#include "ship.h"



void entClass::debugPosOut() {
    ++c;
    std::cout << xPos << yPos << ++c;
}


void entClass::debugVelOut() {
    ++c;
    std::cout << xVel << yVel << ++c;
}


void entClass::isBulletDebug(int code) {
    if (isBullet && isActive && (10 < code) && (20 > code)) {
        std::cout << "debug: " << code;
    }
}


void entClass::initDebugCircle() {
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


void entClass::updateDebugCircle() {
    sf::Color col;
    if (debugOverlap) { col = sf::Color(250, 0, 0); }
    else { col = sf::Color(0, 250, 0); }
    debugCircle.setOutlineColor(col);
    debugCircle.setPosition(xPos, yPos);
}

void entClass::initEnt(sf::Texture& entTexIn, int xPosIn, int yPosIn, float scaleIn) {
    xPos = xPosIn; yPos = yPosIn;
    entSpr.setTexture(entTexIn);
    entSpr.setScale(scaleIn, scaleIn);
    initDebugCircle();
}


void entClass::rotSpr(int degIn) {
    entSpr.setRotation(degIn);
}


void entClass::renderEnt(sf::RenderWindow& winIn) {
    entSpr.setPosition(xPos + sprOffsetX, yPos + sprOffsetY);
    winIn.draw(entSpr);
    if (drawDebugCircle) {
        updateDebugCircle();
        winIn.draw(debugCircle);
    }
}


void entClass::setPos(float xPosIn, float yPosIn) {
    xPos = xPosIn; yPos = yPosIn;
}


void entClass::accelEnt(float xAccelIn, float yAccelIn) {
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


void entClass::mvEnt(float elapsedTimeSinceLastFrame, float xDisplace, float yDisplace, int xBoundMin, int xBoundMax, int yBoundMin, int yBoundMax, entStore* entStorePtr) {
    // cant move outside of x/y bounds
    xPos += xDisplace * elapsedTimeSinceLastFrame;
    yPos += yDisplace * elapsedTimeSinceLastFrame;

    if (scrollingEnt && (xPos < xBoundMin)) {
        respawnEntOffscreen(xBoundMax, yBoundMax, entStorePtr);
    }

    if (isBullet && (xPos > xBoundMax)) {
        isActive = false;
    }

    // clamp the value to bounds (converted from ints to floats (bcs of screen size being an int))
    if (isShip) {
        xPos = std::max(static_cast<float>(xBoundMin + entSizeX), std::min(xPos, static_cast<float>(xBoundMax - entSizeX)));
    }
    yPos = std::max(static_cast<float>(yBoundMin), std::min(yPos, static_cast<float>(yBoundMax - entSizeY)));
}


bool entClass::checkCircleColEntWrapper(entClass* entToCheck) {
    // returns true if entToCheck is overlapping with this ent
    // true if overlapping
    float thisEntCenterPosX = (xPos)+radius;
    float thisEntCenterPosY = (yPos)+radius;
    float entToCheckCenterPosX = (entToCheck->xPos) + entToCheck->radius;
    float entToCheckCenterPosY = (entToCheck->yPos) + entToCheck->radius;
    float minDist = radius + entToCheck->radius;

    return checkCircleColRaw(minDist, thisEntCenterPosX, thisEntCenterPosY, entToCheckCenterPosX, entToCheckCenterPosY);
}


bool entClass::checkCircleColValWrapper(float foreignXPosOrigin, float foreignYPosOrigin, float foreignRadius) {
    // true if overlapping
    float thisEntCenterPosX = (xPos)+radius;
    float thisEntCenterPosY = (yPos)+radius;
    float entToCheckCenterPosX = foreignXPosOrigin + foreignRadius;
    float entToCheckCenterPosY = foreignYPosOrigin + foreignRadius;
    float minDist = foreignRadius + radius;

    return checkCircleColRaw(minDist, thisEntCenterPosX, thisEntCenterPosY, entToCheckCenterPosX, entToCheckCenterPosY);
}


bool entClass::checkCircleColRaw(int minDistIn, float objACntrPosXIn, float objACntrPosYIn, float objBCntrPosXIn, float objBCntrPosYIn) {
    float dist = (objACntrPosXIn - objBCntrPosXIn) * (objACntrPosXIn - objBCntrPosXIn) + (objACntrPosYIn - objBCntrPosYIn) * (objACntrPosYIn - objBCntrPosYIn);
    dist = sqrtf(dist);
    return dist <= minDistIn;
}


void entClass::updateEntPos(float elapsedTimeSinceLastFrame, int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn, entStore* entStorePtr) {
	// auto update entPos using current velocity
	// assumes velocity is already updated
	// use mvEnt if you want custom velocity calues 
	mvEnt(elapsedTimeSinceLastFrame, xVel, yVel, xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn, entStorePtr);
}


void entClass::respawnEntOffscreen(int xBoundMaxIn, int yBoundMaxIn, entStore* entStorePtr) {
	// the function to "destory" and "respawn" pooled ents
	lifetime = 0;
	setPos((float)(xBoundMaxIn + (rand() % 300)), (float)(rand() % (yBoundMaxIn - ASTSIZE)));
}

