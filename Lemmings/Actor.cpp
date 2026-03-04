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
    return m_isLaunchable;
}
void Actor::setLaunchability(bool val) {
    m_isLaunchable = val;
}
bool Actor::isAlive() const {return m_isAlive;}
void Actor::setAlive(bool value) {m_isAlive = value;}




FloorBrick::FloorBrick(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_FLOOR, xInit, yInit, world, true) {}

void FloorBrick::doSomething() {return;}


IceMonster::IceMonster(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_ICE_MONSTER, xInit, yInit, world), m_ticksSinceMove(0) {}

void IceMonster::doSomething() {
    m_ticksSinceMove++;
    if (getWorld()->killLemming(getCoord())) {
        return;
    }
    
    if (m_ticksSinceMove == 10) {
        m_ticksSinceMove = 0;
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
}

LemmingFactory::LemmingFactory(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_LEMMING_FACTORY, xInit, yInit, world), m_ticksSinceLemming(0) {}

void LemmingFactory::doSomething() {
    m_ticksSinceLemming ++;
    if (m_ticksSinceLemming >= 100) {
        if (getWorld()->getLemmingsSpawned() < 10) {
            Coord c = getCoord();
            getWorld()->addActor(new Lemming(c.x, c.y, getWorld()));
            getWorld()->incrementLemmingsSpawned();
            
        }
        m_ticksSinceLemming -= 100;
    }
    return;
}


Lemming::Lemming(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_LEMMING, xInit, yInit, world, false ,true), m_movementState(-1), m_ticksSinceMove(-1), m_distanceFalling(0), m_saved(false) , m_upwardSteps(0), m_targetBounceHeight(0){}
void Lemming::doSomething() {
    m_ticksSinceMove ++;

    if (!isAlive()) {
        return;
    }
    if ((m_movementState == 0 && m_ticksSinceMove < 4) || (m_movementState != 0 && m_ticksSinceMove < 2)) {
        return;
    }
    m_ticksSinceMove = 0;
    int closestPheromoneDirection = getWorld()->getClosestAttractorDirection(getCoord());
    if (closestPheromoneDirection != none) {
        setDirection(closestPheromoneDirection);
    }
    if (m_movementState != 2) {
        int didActorBounce = getWorld()->bounceActor(getCoord(), m_distanceFalling, this);
        if (didActorBounce == 1){
            m_upwardSteps = 0;
            m_movementState = 2;
        }
    }
    
    
    
    if (m_movementState == -1){
        m_movementState = 0;
        doWalking();
    }
    else if (m_movementState == 0) {
        doWalking();
    }
    else if (m_movementState == 1){
        doFalling();
    }
    else if (m_movementState == 2) {
        doBouncing();
    }
    else if (m_movementState == 3) {
        doClimbing();
    }
    
    return;
    
}
void Lemming::doWalking() {
    if (getWorld()->isClimbableAt(getCoord())) {
        m_movementState = 3;
        return;
    }
    
    Coord oneForward = getTargetCoord(getDirection());
    Coord belowNext = getTargetCoord(oneForward, down);
    
    if (getWorld()->isFloorAt(oneForward)) {
        if (getDirection() == left) {
            setDirection(right);
        }
        else {
            setDirection(left);
        }
    }
    else if (getWorld()->isFloorAt(belowNext)) {
        moveTo(oneForward);
    }
    
    else {
        m_movementState = 1;
        m_distanceFalling = 0;
        moveTo(oneForward);
    }
}
void Lemming::doFalling(){
    if (getWorld()->isClimbableAt(getCoord())) {
        m_movementState = 3;
        return;
    }
    Coord below = getTargetCoord(down);

    if (!getWorld()->isFloorAt(below)) {
        moveTo(below);
        m_distanceFalling++;
    }
    else {
        if (m_distanceFalling > 5) {
            getWorld()->killLemming(getCoord());
            return;
        }
        m_distanceFalling = 0;
        m_movementState = 0;
    }
}

void Lemming::doClimbing() {
    if (!getWorld()->isClimbableAt(getCoord())) {
        m_movementState = 0;
        return;
    }
    Coord above = getTargetCoord(up);
    if (above.y <= 0 || getWorld()->isFloorAt(above)) {
        return;
    }
    moveTo(above);
    
}
void Lemming::doBouncing() {
    if (getWorld()->isClimbableAt(getCoord())) {
        m_movementState = 3;
        return;
    }
    if (m_upwardSteps < m_targetBounceHeight) {
        Coord above = getTargetCoord(up);
        if (above.y > 0 && !getWorld()->isFloorAt(above)) {
            moveTo(above);
            m_upwardSteps++;
            if (m_upwardSteps < m_targetBounceHeight){
                return;
            }
        }
    }
    Coord oneForward = getTargetCoord(getDirection());
    if (getWorld()->isFloorAt(oneForward)) {
        if (getDirection() == left) {
            setDirection(right);
        }
        else {
            setDirection(left);
        }
    }
    else {
        m_upwardSteps = 0;
        moveTo(oneForward);
    }
    m_movementState = 1;
    m_distanceFalling = 0;
    
    
}


void Lemming::save() {
    m_saved = true;
    getWorld()->playSound(SOUND_LEMMING_SAVED);
}
void Lemming::kill() {
    setAlive(false);
    getWorld()->playSound(SOUND_LEMMING_DIE);
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
                if (oneForward.y <= VIEW_HEIGHT-2)
                    moveTo(up);
                break;
            }
            case KEY_PRESS_DOWN: {
                Coord oneForward = getTargetCoord(down);
                if (oneForward.y >= 1)
                    moveTo(down);
                break;
            }

            default:
                getWorld()->attemptToolPlace(getCoord(), toupper(keyPressed));
                break;
        }
        
        
    }
    
    
    
    return;
}


Bonfire::Bonfire(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_BONFIRE, xInit, yInit, world) {}
void Bonfire::doSomething() {
    getWorld()->killLemming(getCoord());
}


Exit::Exit(int xInit, int yInit, StudentWorld* world)
    : Actor(IID_EXIT, xInit, yInit, world) {}
void Exit::doSomething() {
    getWorld()->saveLemming(getCoord());
}




Tool::Tool(int image, int xInit, int yInit, StudentWorld* world, int direction)
    : Actor(image, xInit, yInit, world) {
        setDirection(direction);
    }
void Tool::doSomething() {return;}

Trampoline::Trampoline(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_TRAMPOLINE, xInit, yInit, world) {}
void Trampoline::doSomething() {
    
    
    return;
    
}
int Trampoline::getLaunchAmount(int fallHeight) const {
    if (fallHeight < 0)
        return 0;
    
    return fallHeight-1;
}


Spring::Spring(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_SPRING, xInit, yInit, world) {}
void Spring::doSomething() {
    
    return;
}
int Spring::getLaunchAmount(int fallHeight) const {
    return 15;
}


Net::Net(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_NET, xInit, yInit, world) {}
void Net::doSomething() {return;}

OneWayDoor::OneWayDoor(int xInit, int yInit, StudentWorld* world, int direction)
    : Tool(IID_ONE_WAY_DOOR, xInit, yInit, world, direction) {}
void OneWayDoor::doSomething() {
    if (getWorld()->swapActorDirection(getCoord(), getDirection())) {
        return;
    }
    return;
}

Pheromone::Pheromone(int xInit, int yInit, StudentWorld* world)
    : Tool(IID_PHEROMONE, xInit, yInit, world) {}
void Pheromone::doSomething() {return;}


