#pragma once

#include "entity.h"
#include "ship.h"


struct entStore {
    std::vector<entClass> entVect = {}; // where all ents are actually stored in memory, except ship
    std::vector<entClass*> entPtrsVect = {}; // pointers to all ents, inc bullets and ship
    std::vector<entClass*> bulletPtrPool = {}; // pointers to all bullets
    ship* shipPtr; // pointer to ship ent


    void drawEntStore(sf::RenderWindow&);

    void updateEntsPositions(float, int, int, int, int);

    void createEntPtrsVect();

    void perFrameCollisions(entClass*);


    void debugIfBulletExist(int);

    void deactivateAllEnt();
};

