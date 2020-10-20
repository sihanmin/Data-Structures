#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Field.h"
#include <string>
#include <list>
#include "Compiler.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {m_tick = 0; m_winner = 0;}
    
    virtual ~StudentWorld()
    {}
    
    
    bool canGo(int x, int y); // check if this step is blocked
    
    // features
    bool bite(int x, int y, Actor* except, int amount);
    // called by ant and grasshopper to bite
    void stun(int x, int y);    // called by water to stun
    void poison(int x, int y);  // called by poison
    
    // add things
    void addAdultGrasshopper(int x, int y);
    void addNewAnt(int x, int y, Compiler* compiler, int ID, int colony);   // called by anthills
    void addPheromone(int x, int y, int colony);    // called by ants
    
    // about food
    bool hasFood(int x, int y, std::list<Actor*>::iterator &it);
    int pickFood(int x, int y, int amount); // called by insects to pick up food
    void dropFood(int x, int y, int amount);
    
    // for ants
    void updateAnt(int x, int y, int colony);
    bool hasEnemy(int x, int y, int colony);
    bool findPheromone(int x, int y, int colony);
    bool danger(int x, int y, int colony);
    
    // other things
    int getCurrentTicks() {return m_tick;}
    void updateDisplayText();
    virtual int init()
    {
        int result;
        result = loadField();
        
        if (result == GWSTATUS_LEVEL_ERROR)
            return GWSTATUS_LEVEL_ERROR;
        
        
        m_tick = 0;
        return GWSTATUS_CONTINUE_GAME;
    }
    
    virtual int move()
    {
        // This code is here merely to allow the game to build, run, and terminate after you hit enter.
        // Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
        m_tick++; // update the current tick # in the simulation
        
        //std::cout << m_tick << std::endl;
        
        // The term "actors" refers to all ants, anthills, poison, pebbles,
        // baby and adult grasshoppers, food, pools of water, etc.
        // Give each actor a chance to do something
        for (int i = 0; i < 64*64; i++)
        {
            moveThisList(graph[i][1]);
            moveThisList(graph[i][0]);
        }
        
        
        for (int x = 0; x < 64; x++)
        {
            for (int y = 0; y < 64; y++)
            {
                update(x, y, 0);
                update(x, y, 1);
            }
        }
        
        
        // Remove newly-dead actors after each tick
        //removeDeadSimulationObjects(); // delete dead simulation objects
        
        // Update the simulation Status Line
        updateDisplayText(); // update the ticks/ant stats text at screen top
        
        //If the simulation’s over (ticks == 2000) then see if we have a winner
        if (m_tick == 2000)
        {
            if (m_antNum[m_winner] > 5)
            {
                setWinner(m_bugName[m_winner]);
                return GWSTATUS_PLAYER_WON;
                
            }
            else
                return GWSTATUS_NO_WINNER;
        }
        
        //the simulation is not yet over, continue!
        return GWSTATUS_CONTINUE_GAME;
    }
    
    virtual void cleanUp()
    {
        for (int i = 0; i < 64*64; i++)
        {
            deleteList(graph[i][0]);
            deleteList(graph[i][1]);
        }
        for (int i = 0; i < m_players; i++)
        {
            if (m_compiler[i] != nullptr)
                delete m_compiler[i];
            m_compiler[i] = nullptr;
        }
    }
    
private:
    int m_tick;
    int m_antNum[4] = {0, 0, 0, 0};
    int m_winner;
    int m_players;
    Compiler* m_compiler[4];
    std::string m_bugName[4] = {"", "", "", ""};
    std::list<Actor*> graph[64*64][2];   // 2-D graph to 1-D array
    // graph[n][0] is a list of insects and graph[n][1] is a list of other things
    
    //void freeMemory(std::list<Actor*> &free);
    void moveThisList(std::list<Actor*> &cur);
    //void resetStatus(std::list<Actor*> &cur);
    int loadField();
    void update(int x, int y, int c);
    void deleteList(std::list<Actor*> &cur);
};

#endif // STUDENTWORLD_H_
