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
: GameWorld(assetPath), m_level(Level(assetPath)), m_score(0), m_lemmingsSpawned(0), m_lemmingsSaved(0), m_lemmingsDead(0), m_ticksRemaining(2000)
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
    
    m_actorList.push_back(new Player(this));
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
    m_toolList = m_level.getTools();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_ticksRemaining --;
    
    for (int i = 0; i < m_actorList.size(); i++) {
        m_actorList.at(i) -> doSomething();
    }
    // This code is here merely to allow the game to build, run, and terminate after you type q

    setGameStatText("Score: " + printNumber(getScore(), 5)
                    + " Level: " + printNumber(getLevel(), 2)
                    + " Lives: " + printNumber(getLives(), 2)
                    + " Saved: " + printNumber(m_lemmingsSaved, 2)
                    + " Tools: " + printTools()
                    + " Time left: " + printNumber(m_ticksRemaining, 4));

    if (m_lemmingsDead > 5 || (m_ticksRemaining == 0 && m_lemmingsSaved < 5)) {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    if (m_ticksRemaining == 0 && m_lemmingsSaved >= 5) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    //THERES MORE IF STATEMENTS TO DO HERE!!!!!
    
    
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

void StudentWorld::addActor(Actor* a) {
    m_actorList.push_back(a);
}

std::string StudentWorld::printNumber(int number, int places){
    string out = "";
    string strNumber = to_string(number);
    int count = 0;
    for (int i = 0; i < places; i++) {
        if (places - i > strNumber.size()) {
            out += '0';
        }
        else {
            out += strNumber[count];
            count ++;
        }
    }

    
    return out;
}
std::string StudentWorld::printTools(){
    if (m_toolList.size() == 0) {
        return "None";
    }
    return m_toolList;
}
