#pragma once

#include "entity.h"
#include "ship.h"


struct entStore {
    //std::vector<entClass*> entVect = {};
    std::vector<entClass> entVect = {};
    std::vector<entClass*> entPtrsVect = {};
    //entClass entArr[1024];
    std::vector<entClass*> bulletPtrPool = {};
    ship* shipPtr; // cant store it as a ship due to circualar depedency, need to split this obj into a diff file if thats needed


    void drawEntStore(sf::RenderWindow&);

    void updateEntsPositions(float, int, int, int, int);

    void createEntPtrsVect();

    void perFrameCollisions(entClass*);


    void debugIfBulletExist(int);

    void deactivateAllEnt();
};

