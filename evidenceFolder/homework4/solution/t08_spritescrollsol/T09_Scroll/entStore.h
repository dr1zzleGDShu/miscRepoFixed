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


    void drawEntStore(sf::RenderWindow& winIn) {
        //shipPtr->renderEnt(winIn);
        for (entClass* i : entPtrsVect) {
            if (i->isActive) {
                i->renderEnt(winIn);
            }
        }
    }

    void updateEntsPositions(float elapsedTimeSinceLastFrame, int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
        //shipPtr->updateEntPos(elapsedTimeSinceLastFrame, xBoundMinIn, xBoundMaxIn, yBoundMinIn, yBoundMaxIn, this);
        int c = 0;
        for (entClass* i : entPtrsVect) {
            if (i->isActive) {
                i->updateEntPos(elapsedTimeSinceLastFrame, xBoundMinIn - 200, xBoundMaxIn, yBoundMinIn, yBoundMaxIn + 200, this);
                updateDebugOverlap(i);
                i->lifetime += 1;
            }
        }
    }


    void createEntPtrsVect() {
        entPtrsVect.push_back(shipPtr);
        for (entClass& i : entVect) {
            entPtrsVect.push_back(&i);
        }
    }


    void updateDebugOverlap(entClass*);


    void debugIfBulletExist(int codeIn) {
        for (entClass& i : entVect) {
            i.isBulletDebug(codeIn);
        }
    }
};

