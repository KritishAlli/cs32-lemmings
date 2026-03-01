#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// delete this line if it doesnt work and debug elsewhere
class StudentWorld;

class Actor : public GraphObject {
public:
    Actor(int image, int xInit, int yInit, StudentWorld* world);
    virtual ~Actor();
    virtual void doSomething() = 0;

    StudentWorld* getWorld();
private:

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

#endif // ACTOR_H_
