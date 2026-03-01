#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int image, int xInit, int yInit, StudentWorld* world)
    : GraphObject(image, Coord(xInit, yInit), right), m_world(world) {}
Actor::~Actor() {}

StudentWorld* Actor::getWorld(){
    return m_world;
}


FloorBrick::FloorBrick(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_FLOOR, xInit, yInit, world) {}

void FloorBrick::doSomething() {return;}


IceMonster::IceMonster(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_ICE_MONSTER, xInit, yInit, world) {}

void IceMonster::doSomething() {
    
    int direction = getDirection();
    Coord oneForward = getTargetCoord(direction);
    Coord belowForward = getTargetCoord(oneForward, GraphObject::down);
    
    if (getWorld()->isFloorAt(oneForward) || !getWorld()->isFloorAt(belowForward)) {
        if (direction == left) {
            setDirection(right);
        }
        else {
            setDirection(left);
        }
    }
    else {
        moveTo(oneForward);
    }
}



// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
