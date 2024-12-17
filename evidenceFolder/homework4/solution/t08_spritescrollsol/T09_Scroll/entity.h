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
    float sprOffsetX = 0, sprOffsetY = 0; // where sprite renders from, relative to ent origin
    int dc = 0; // a counter for debug 
    const float maxVel = 600;
    bool scrollingEnt = true; // if true then ents "respawn" when they hit the left side of the screen
    float radius = 40; //only supports circle collisions rn so no x/y radius
    bool debugOverlap = false; // debug: is ent currently colliding with anything
    sf::CircleShape debugCircle; // debug: a circle used to desplay debug overlap
    bool drawDebugCircle = true; // debug: if false dont draw the debug circle
    int lifetime = 0; // time since item last "spawned", iin frames
                    // TODO mby should be based on delta time rather then frames
    int LIFETIMERESPAWNLIMIT = 4; // how many frames after spawning an ent can be respawned at at diff location
                    // used to avoid ents overlapping on spawn
    bool isBullet = false;
    bool isAsteroid = false;
    bool isActive = true;
    bool isShip = false;
    float entSizeX = 100; // used for keeping ent within screen bounds, not collision
    float entSizeY = 180; 
    float rcsCoeff = 0.998; // coeff ship uses to show down per frame, "air resistance"
                    // TODO should be a smaller value and using delta time when used
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


