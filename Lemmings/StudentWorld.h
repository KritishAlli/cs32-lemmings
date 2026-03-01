#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Level::MazeEntry actorAt(Coord p);
    bool isFloorAt(Coord p);

    

private:
    std::vector<Actor*> m_actorList;
    std::string m_toolList;
    Level m_level;
    int m_score;
    int m_levelNumber;
    int m_ticksRemaining;
    int m_lemmingsSpawned;
    int m_lemmingsDead;
    int m_lemmingsSaved;
    std::string printNumber(int number, int places);
    std::string printTools();


    
};

#endif // STUDENTWORLD_H_
