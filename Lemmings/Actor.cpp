#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int image, int xInit, int yInit, StudentWorld* world, bool solidity, bool launchability, bool isAlive)
    : GraphObject(image, Coord(xInit, yInit)), m_world(world), m_isSolid(solidity), m_isLaunchable(launchability), m_isAlive(isAlive) {}
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
bool Actor::isAlive() const {return m_isAlive;}




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
    : Actor(IID_LEMMING_FACTORY, xInit, yInit, world), m_ticksSinceLemming(0) {}

void LemmingFactory::doSomething() {
    m_ticksSinceLemming ++;
    if (m_ticksSinceLemming >= 100) {
        if (getWorld()->getLemmingsSpawned() < 10) {
            Coord c = getCoord();
            getWorld()->addActor(new Lemming(c.x, c.y, getWorld()));
            
        }
        m_ticksSinceLemming -= 100;
    }
    return;
}


Lemming::Lemming(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_LEMMING, xInit, yInit, world), m_movementState(0), m_ticksSinceMove(0){}
void Lemming::doSomething() {
    m_ticksSinceMove ++;
    if (!isAlive()) {
        return;
    }
    if (m_movementState == 0) {
        if (m_ticksSinceMove == 4) {
            m_ticksSinceMove = 0;
            int direction = getDirection();
            Coord oneForward = getTargetCoord(direction);
            if (getWorld()->isFloorAt(oneForward)) {
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
    }
    else {
        if (m_ticksSinceMove == 2) {
            m_ticksSinceMove = 0;
            int direction = getDirection();
            Coord oneForward = getTargetCoord(direction);
            if (getWorld()->isFloorAt(oneForward)) {
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
    }
    
    
    return;
    
}


Player::Player(StudentWorld* world)
    : Actor(IID_PLAYER, VIEW_WIDTH/2, VIEW_HEIGHT/2, world) {}

void Player::doSomething() {
    
    int keyPressed = 0;
    
    if (getWorld()->getKey(keyPressed)) {
        
        switch (keyPressed) {
            case KEY_PRESS_LEFT: {
                Coord oneForward = getTargetCoord(left);
                if (oneForward.x >= 1)
                    moveTo(left);
                break;
            }
            case KEY_PRESS_RIGHT: {
                Coord oneForward = getTargetCoord(right);
                if (oneForward.x <= VIEW_WIDTH-2)
                    moveTo(right);
                break;
            }
            case KEY_PRESS_UP: {
                Coord oneForward = getTargetCoord(up);
                if (oneForward.y >= 1)
                    moveTo(up);
                break;
            }
            case KEY_PRESS_DOWN: {
                Coord oneForward = getTargetCoord(down);
                if (oneForward.y <= VIEW_HEIGHT-2)
                    moveTo(down);
                break;
            }

            default:
                std::cout << keyPressed;
                break;
        }
        
        
    }
    
    
    
    return;
}


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


