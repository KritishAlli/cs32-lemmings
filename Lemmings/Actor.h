#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// delete this line if it doesnt work and debug elsewhere
class StudentWorld;

class Actor : public GraphObject {
public:
    Actor(int image, int xInit, int yInit, StudentWorld* world, bool solidity = false, bool launchability = false, bool isAlive = true);
    virtual ~Actor();
    virtual void doSomething() = 0;

    StudentWorld* getWorld();
    bool isSolid() const;
    void setSolidity(bool val);
    bool isLaunchable() const;
    void setLaunchability(bool val);
    bool isAlive() const;
    void setAlive(bool value);
    virtual bool isSaveable() const {return false;}
    virtual bool isKillable() const {return false;}
    virtual bool canChangeDirection() const {return false;}
    virtual bool isSaved() const {return false;}
    virtual void save() {};
    virtual void kill() {};
    virtual bool isLemmingAttractor() const {return false;}
    virtual bool isClimbable() const {return false;}
    virtual void setTargetLaunch(int height) {}
    virtual void setMovementState(int state) {}
    virtual int getFallingHeight() const {return 0;}
    virtual bool isLauncher() const {return false;}
    virtual int getLaunchAmount(int fallHeight) const {return -1;}



private:
    bool m_isSolid;
    bool m_isLaunchable;
    bool m_isAlive;
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
    bool canChangeDirection() const override {return true;}

private:
    int m_ticksSinceMove;

};
class LemmingFactory : public Actor {
public:
    LemmingFactory(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
private:
    int m_ticksSinceLemming;
    int m_lemmingsSpawned;
};
class Lemming : public Actor {
public:
    Lemming(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
    bool isSaved() const override {return m_saved;}
    void setSaved(bool value) {m_saved = value;}
    bool isSaveable() const override {return true;}
    bool isKillable() const override {return true;}
    bool canChangeDirection() const override {return true;}
    void save() override;
    void kill() override;
    void doWalking();
    void doClimbing();
    void doFalling();
    void doBouncing();
    void setTargetBounceHeight(int height) {m_targetBounceHeight = height;}
    void setMovementState(int state) override {m_movementState = state;}
    bool isBouncing() {return m_movementState == 2;}
    void setTargetLaunch(int height) override {m_targetBounceHeight = height;}
    int getFallingHeight() const override {return m_distanceFalling;}
private:
    int m_ticksSinceMove;
    int m_distanceFalling;
    bool m_saved;
    int m_upwardSteps;
    int m_targetBounceHeight;

    // -1 - idle, 0 - walking, 1 - falling, 2 - bouncing, 3 - climbing
    int m_movementState;
};
class Player : public Actor {
public:
    Player(StudentWorld* world);
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
    Tool(int image, int xInit, int yInit, StudentWorld* world, int direction = right);
    void doSomething() override;
};

class Trampoline : public Tool {
public:
    Trampoline(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
    virtual bool isLauncher() const override {return true;}
    virtual int getLaunchAmount(int fallHeight) const override;
};
class Spring : public Tool {
public:
    Spring(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
    virtual bool isLauncher() const override {return true;}
    virtual int getLaunchAmount(int fallHeight) const override;
};
class Net : public Tool {
public:
    Net(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
    bool isClimbable() const override {return true;}

};
class OneWayDoor : public Tool {
public:
    OneWayDoor(int xInit, int yInit, StudentWorld* world, int direction);
    void doSomething() override;
};
class Pheromone : public Tool {
public:
    Pheromone(int xInit, int yInit, StudentWorld* world);
    void doSomething() override;
    bool isLemmingAttractor() const override {return true;}
};


#endif // ACTOR_H_
