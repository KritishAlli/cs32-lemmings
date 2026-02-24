#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int image, int xInit, int yInit, StudentWorld* world)
    : m_image(image), m_posx(xInit), m_posy(yInit), m_world(world) {}
Actor::~Actor() {}
int Actor::getXPos(){
    return m_posx;
}

int Actor::getYPos() {
    return m_posy;
}

void Actor::setXY(int xNew, int yNew){
    m_posx = xNew;
    m_posy = yNew;
}
StudentWorld* Actor::getWorld(){
    return m_world;
}


FloorBrick::FloorBrick(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_FLOOR, xInit, yInit, world) {}

void FloorBrick::doSomething() {return;}


IceMonster::IceMonster(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_ICE_MONSTER, xInit, yInit, world), facingLeft(true) {}

void IceMonster::doSomething() {
    int curX = getXPos();
    int curY = getYPos();
    if (facingLeft) {
        if (getWorld()->actorAt(curX - 1, curY) == "floor") {
            facingLeft = !facingLeft;
        }
        else if (getWorld()->actorAt(curX - 1, curY+1) != "floor") {
            facingLeft = !facingLeft;
        }
        else {
            setXY(curX - 1, curY);
        }
    }
    else {
        if (getWorld()->actorAt(curX + 1, curY) == "floor") {
            facingLeft = !facingLeft;
        }
        else if (getWorld()->actorAt(curX + 1, curY+1) != "floor") {
            facingLeft = !facingLeft;
        }
        else {
            setXY(curX + 1, curY);
        }
    }
}



// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
