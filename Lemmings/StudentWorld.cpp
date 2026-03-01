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
: GameWorld(assetPath), m_level(Level(assetPath)), m_ticksRemaining(2000)
{
}
StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    std::string curLevel = "level00.txt";
    Level::LoadResult result = m_level.loadLevel(curLevel);
    
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
            else if (item == Level::lemming_factory) {
                m_actorList.push_back(new LemmingFactory(x,y,this));
            }
            else if (item == Level::lemming_exit) {
                m_actorList.push_back(new Exit(x,y,this));
            }
            else if (item == Level::trampoline) {
                m_actorList.push_back(new Trampoline(x,y,this));
            }
            else if (item == Level::bonfire) {
                m_actorList.push_back(new Bonfire(x,y,this));
            }
            else if (item == Level::spring) {
                m_actorList.push_back(new Spring(x,y,this));
            }
            else if (item == Level::net) {
                m_actorList.push_back(new Net(x,y,this));
            }
            else if (item == Level::left_one_way_door) {
                m_actorList.push_back(new OneWayDoor(x,y,this));
            }
            else if (item == Level::right_one_way_door) {
                m_actorList.push_back(new OneWayDoor(x,y,this));
            }
            else if (item == Level::pheromone) {
                m_actorList.push_back(new Pheromone(x,y,this));
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
Level::MazeEntry StudentWorld::actorAt(Coord p){
    Level::MazeEntry item = m_level.getContentsOf(p);
    return item;
}

bool StudentWorld::isFloorAt(Coord p){
    Level::MazeEntry item = m_level.getContentsOf(p);
    return item == Level::floor;
}
