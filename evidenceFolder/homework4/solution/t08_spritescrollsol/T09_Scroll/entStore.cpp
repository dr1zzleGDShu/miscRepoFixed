#include "entity.h"
#include "entStore.h"



void entStore::drawEntStore(sf::RenderWindow& winIn) {
	// draws all ents in the store
    for (entClass* i : entPtrsVect) {
        if (i->isActive) {
            i->renderEnt(winIn);
        }
    }
}


void entStore::updateEntsPositions(float elapsedTimeSinceLastFrame, int xBoundMinIn, int xBoundMaxIn, int yBoundMinIn, int yBoundMaxIn) {
	// moves all ents in the store, based on their velocity
	// also collions per frame logic done here 
	// also lifetime of frames is incremented here
    int c = 0;
    for (entClass* i : entPtrsVect) {
        if (i->isActive) {
            i->updateEntPos(elapsedTimeSinceLastFrame, xBoundMinIn - 200, xBoundMaxIn, yBoundMinIn, yBoundMaxIn + 200, this);
            perFrameCollisions(i);
            i->lifetime += 1;
        }
    }
}


void entStore::createEntPtrsVect() {
	// popluates entPtrsVect with pointers to all ents in the store
    entPtrsVect.push_back(shipPtr);
    for (entClass& i : entVect) {
        entPtrsVect.push_back(&i);
    }
}


void entStore::debugIfBulletExist(int codeIn) {
	// used for debug
    for (entClass& i : entVect) {
        i.isBulletDebug(codeIn);
    }
}


void entStore::deactivateAllEnt() {
	// deactives all ents in the store
    for (entClass& i : entVect) {
        i.isActive = false;
    }
}


void entStore::perFrameCollisions(entClass* entIn) {
	// updates the debug overlap (red/green overlap cicles)
	// also does logic for stuff does overlap
	// entIn is the ent that is being checked
	entIn->debugOverlap = false;
	for (entClass& i : entVect) { // iterates through all other ents 
		if (i.isActive) { // ignore inactive ents
			if (i.checkCircleColEntWrapper(entIn)) { // is i overlapping with entIn
				if (&i != entIn) { // if i and entIn are diffrent
					entIn->debugOverlap = true;
					// if i is asteroid that has just spawned
					if ((i.lifetime < i.LIFETIMERESPAWNLIMIT) && i.isAsteroid) {
						// respawn the ent to avoid overlapping astoids
						i.respawnEntOffscreen(GC::SCREEN_RES.x, GC::SCREEN_RES.y, this);
						entIn->debugOverlap = false;
					}
					// if a bullet hit an asteroid
					if (i.isBullet && entIn->isAsteroid) {
						// respawn the ent (and destroy it)
						entIn->respawnEntOffscreen(GC::SCREEN_RES.x, GC::SCREEN_RES.y, this);
						entIn->debugOverlap = false;
						i.isActive = false;
					}
					// if the ship hits an asteroid, and the spawn invuln frames are up
					if (entIn->isShip && !i.isBullet && entIn->lifetime > GC::SHIPSPAWNINVULN) {
						// game fail state
						// when ship deactives, will render death message
						entIn->isActive = false;
						deactivateAllEnt();
					}
				}
			}
		}
	}
}