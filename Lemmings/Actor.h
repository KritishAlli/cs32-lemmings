#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// delete this line if it doesnt work and debug elsewhere
class StudentWorld;

class Actor {
public:
    Actor(int image, int xInit, int yInit, StudentWorld* world);
    virtual ~Actor();
    virtual void doSomething() = 0;
    int getXPos();
    int getYPos();
    void setXY(int xNew, int yNew);
    StudentWorld* getWorld();
private:
    int m_image;
    int m_posx;
    int m_posy;
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
private:
    bool facingLeft;
};

#endif // ACTOR_H_
