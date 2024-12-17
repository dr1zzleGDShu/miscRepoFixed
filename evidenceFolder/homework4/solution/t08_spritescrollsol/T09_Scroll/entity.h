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


    void debugPosOut();

    void debugVelOut();

    void isBulletDebug(int);

    void initDebugCircle();

    void updateDebugCircle();

    void initEnt(sf::Texture&, int, int, float);

    void rotSpr(int);

    void renderEnt(sf::RenderWindow&);

    void setPos(float, float);

    void accelEnt(float, float);

    void mvEnt(float, float, float, int, int, int, int, entStore*);

    void updateEntPos(float, int, int, int, int, entStore*);

    void respawnEntOffscreen(int , int , entStore* );

    bool checkCircleColEntWrapper(entClass*);

    bool checkCircleColValWrapper(float, float, float);

    bool checkCircleColRaw(int, float, float, float, float);
};


