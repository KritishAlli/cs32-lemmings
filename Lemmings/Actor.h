#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// delete this line if it doesnt work and debug elsewhere
class StudentWorld;

class Actor : public GraphObject {
public:
    Actor(int image, int xInit, int yInit, StudentWorld* world, bool solidity = false, bool launchability = false);
    virtual ~Actor();
    virtual void doSomething() = 0;

    StudentWorld* getWorld();
    bool isSolid() const;
    void setSolidity(bool val);
    bool isLaunchable() const;
    void setLaunchability(bool val);
private:
    bool m_isSolid;
    bool m_isLaunchable;
    StudentWorld* m_world;

};

class FloorBrick : public Actor {
public:
    FloorBrick(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};

class IceMonster : public Actor {
public:
    IceMonster(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;

};
class LemmingFactory : public Actor {
public:
    LemmingFactory(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Lemming : public Actor {
public:
    Lemming(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Player : public Actor {
public:
    Player(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Bonfire : public Actor {
public:
    Bonfire(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Exit : public Actor {
public:
    Exit(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};



class Tool : public Actor {
public:
    Tool(int image, int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};

class Trampoline : public Tool {
public:
    Trampoline(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Spring : public Tool {
public:
    Spring(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Net : public Tool {
public:
    Net(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class OneWayDoor : public Tool {
public:
    OneWayDoor(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};
class Pheromone : public Tool {
public:
    Pheromone(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
};


#endif // ACTOR_H_
