#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int image, int xInit, int yInit, StudentWorld* world, bool solidity, bool launchability)
    : GraphObject(image, Coord(xInit, yInit)), m_world(world), m_isSolid(solidity), m_isLaunchable(launchability) {}
Actor::~Actor() {}

StudentWorld* Actor::getWorld(){
    return m_world;
}
bool Actor::isSolid() const {
    return m_isSolid;
}
void Actor::setSolidity(bool val) {
    m_isSolid = val;
}
bool Actor::isLaunchable() const {
    return m_isSolid;
}
void Actor::setLaunchability(bool val) {
    m_isLaunchable = val;
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

LemmingFactory::LemmingFactory(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_LEMMING_FACTORY, xInit, yInit, world) {}
void LemmingFactory::doSomething() {return;}


Lemming::Lemming(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_LEMMING, xInit, yInit, world) {}
void Lemming::doSomething() {return;}

Player::Player(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_PLAYER, xInit, yInit, world) {}
void Player::doSomething() {return;}


Bonfire::Bonfire(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_BONFIRE, xInit, yInit, world) {}
void Bonfire::doSomething() {return;}


Exit::Exit(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_EXIT, xInit, yInit, world) {}
void Exit::doSomething() {return;}




Tool::Tool(int image, int xInit, int yInit, StudentWorld* world)
    : Actor(image, xInit, yInit, world) {}
void Tool::doSomething() {return;}

Trampoline::Trampoline(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_TRAMPOLINE, xInit, yInit, world) {}
void Trampoline::doSomething() {return;}


Spring::Spring(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_SPRING, xInit, yInit, world) {}
void Spring::doSomething() {return;}


Net::Net(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_NET, xInit, yInit, world) {}
void Net::doSomething() {return;}

OneWayDoor::OneWayDoor(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_ONE_WAY_DOOR, xInit, yInit, world) {}
void OneWayDoor::doSomething() {return;}

Pheromone::Pheromone(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_PHEROMONE, xInit, yInit, world) {}
void Pheromone::doSomething() {return;}


