#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp
// Do not change or remove the createStudentWorld implementation above.

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_level(Level(assetPath))
{
}
StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    Level::LoadResult result = m_level.loadLevel(assetPath());
    
    if (result == Level::load_fail_file_not_found ||
        result == Level::load_fail_bad_format)
        return -1;
    
    
    for ( int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            Coord cur_coord(x, y);
            Level::MazeEntry item = m_level.getContentsOf(cur_coord);
            if (item == Level::floor) {
                m_actorList.push_back(new FloorBrick(x, y, this));
            }
            else if (item == Level::ice_monster) {
                m_actorList.push_back(new IceMonster(x, y, this));
            }
            
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    for (int i = 0; i < m_actorList.size(); i++) {
        m_actorList.at(i) -> doSomething();
    }
    // This code is here merely to allow the game to build, run, and terminate after you type q

    setGameStatText("Game will end when you type q");
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < m_actorList.size(); i++) {
        delete m_actorList.at(i);
    }
    m_actorList.clear();
}
string StudentWorld::actorAt(int x, int y){
    Coord p(0, 5);
    Level::MazeEntry item = m_level.getContentsOf(p);
    if (item == Level::floor)
        return "floor";
    if (item == Level::ice_monster)
        return "ice-monster";
    return "invalid";
}
