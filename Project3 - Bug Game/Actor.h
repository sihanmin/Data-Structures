#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"
#include "Compiler.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int endurance, StudentWorld* studentWorld, int imageID, int startX, int startY, Direction dir = right, int depth = 0, double size = 0.25)
    :GraphObject(imageID, startX, startY, dir, depth, size)
    {
        m_endurance = endurance;
        m_locOneD = startX + startY*64;
        m_turn = 0;
        m_status = "";
        m_studentWorld = studentWorld;
    }
    virtual ~Actor() {};
    
    // trivial functions
    int getEndurance() const {return m_endurance;}
    int getLoc() const {return m_locOneD;}
    std::string getStatus() const {return m_status;}
    int getTurn() const {return m_turn;}
    StudentWorld* getWorld() const {return m_studentWorld;}
    void updateTurn(int a = 0) {m_turn += a;};  // for insects
    void updateLoc(int x, int y)
    {
        moveTo(x, y);
        m_locOneD = getX()+getY()*64;   //(col, row)
    }
    void updateEndurence(int change) {m_endurance += change;}
    void updateStatus(char cur)
    {
        m_status += cur;
    }
    void clearStatus() {m_status = "";}
    bool checkStatus(char st);
    
    // Identifiers
    virtual bool blockInsect() {return false;}  // pebble
    virtual bool isFood() {return false;}   // food
    virtual bool canBePoisoned() {return false;}    // ant and babygrasshopper
    virtual bool deadDropFood() {return false;} // ant and grasshopper
    virtual bool poisonous() {return false;}
    virtual int checkColony() {return -1;}
    virtual void biteBack() {};
    virtual bool complete() {return false;} // ant maybe complete
    virtual void notComplete() {};
    
    // Serious functions
    virtual void doSomething() = 0;
    
    
    
private:
    int m_endurance;
    int m_locOneD;  // stored its 1-D location
    int m_turn; // turns left to pause
    std::string m_status;  // 'p' - poisoned
    // 's' - stunned
    // 'l' - blocked
    // 'b' - bitten
    // "" - none
    StudentWorld* m_studentWorld;
};



class Insect: public Actor
{
public:
    Insect(int endurance, StudentWorld* studentWorld, int imageID, int startX, int startY, Direction dir = right, int depth = 0, double size = 0.25)
    :Actor(endurance, studentWorld, imageID, startX, startY, dir, depth, size)
    {}
    
    virtual ~Insect(){};
    
    int attemptNextStep(Direction dir);
    
private:
    
};

class Ant: public Insect
{
public:
    Ant(Compiler* compiler, int colony, StudentWorld* studentWorld, int imageID, int startX, int startY)
    : Insect(1500, studentWorld, imageID, startX, startY, none, 1)
    {
        m_compiler = compiler;
        int dir = randInt(1, 4);
        switch (dir)
        {
            case 1: setDirection(up); break;
            case 2: setDirection(right); break;
            case 3: setDirection(down); break;
            case 4: setDirection(left); break;
        }
        m_food = 0;
        m_colony = colony;
        m_ic = 0;
        m_lastRandom = 0;
        m_momX = startX;
        m_momY = startY;
        m_complete = false;
    }
    
    virtual ~Ant(){};
    virtual bool canBePoisoned() {return true;}
    virtual bool deadDropFood() {return true;}
    virtual int checkColony() {return m_colony;}
    virtual bool complete() {return m_complete;}
    virtual void notComplete() {m_complete = false;}
    virtual void doSomething();
    
private:
    int m_colony;
    Compiler* m_compiler;
    int m_food;
    int m_ic;
    int m_lastRandom;
    int m_momX;
    int m_momY; // its anthill's position
    bool m_complete; // this tick has complete
    
    int toNum(std::string s);
    bool interpreter();
    void moveTheAntForward();
    int nextStep();
    void pickupSomeFood();
    void dropSomeFood();
    void eatSomeFood();
    void bite();
    void rotateClockwise();
    void rotateCounterClockwise();
    void faceRandomDirection();
    void generateRandomNumber(int N);
    void emitPheromone();
    bool conditionTrue(int statement);
    bool checkInFront(std::string check);
};

class Grasshopper: public Insect
{
public:
    Grasshopper(int endurance, StudentWorld* studentWorld, int imageID, int startX, int startY)
    :Insect(endurance, studentWorld, imageID, startX, startY, none, 1)
    {m_dis = 0;}
    
    virtual ~Grasshopper(){};;
    
    int getDis() {return m_dis;}
    void updateDis(int a) {m_dis += a;}
    virtual bool deadDropFood() {return true;}
    void pickNewWay();
    
private:
    int m_dis;  // distance to walk in current direction
};

class BabyGrasshopper: public Grasshopper
{
public:
    BabyGrasshopper(StudentWorld* studentWorld, int startX, int startY)
    :Grasshopper(500, studentWorld, IID_BABY_GRASSHOPPER, startX, startY)
    {
        pickNewWay();
    }
    
    virtual ~BabyGrasshopper(){};
    virtual bool canBePoisoned() {return true;} // same for ant
    virtual void doSomething();
    
private:
};

class AdultGrasshopper: public Grasshopper
{
public:
    AdultGrasshopper(StudentWorld* studentWorld, int startX, int startY)
    :Grasshopper(1600, studentWorld, IID_ADULT_GRASSHOPPER, startX, startY)
    {
        pickNewWay();
    }
    
    virtual ~AdultGrasshopper(){};
    virtual void biteBack();
    
    virtual void doSomething();
    
private:
};

class Anthill: public Actor
{
public:
    Anthill(Compiler* compiler, int colony, StudentWorld* studentWorld, int startX, int startY)
    : Actor(8999, studentWorld, IID_ANT_HILL, startX, startY, right, 2)
    {m_colony = colony; m_compiler = compiler;}
    
    virtual ~Anthill(){};
    virtual void doSomething();
    
    
private:
    int m_colony;
    Compiler* m_compiler;
};

class Food: public Actor
{
public:
    Food(int endurance, StudentWorld* studentWorld, int startX, int startY)
    :Actor(endurance, studentWorld, IID_FOOD, startX, startY, right, 2) {};
    virtual ~Food(){};
    virtual void doSomething() {};
    virtual bool isFood() {return true;}
    
private:
    
};

class Pheromone: public Actor
{
public:
    Pheromone(StudentWorld* studentWorld, int imageID, int startX, int startY, int colony)
    :Actor(256, studentWorld, imageID, startX, startY, right, 2)
    {m_colony = colony;}
    virtual ~Pheromone(){};
    virtual void doSomething() {updateEndurence(-1);} //
    virtual int checkColony() {return m_colony;}
    
private:
    int m_colony;
};



class Poison: public Actor
{
public:
    Poison(StudentWorld* studentWorld, int startX, int startY, int ID = IID_POISON)
    :Actor(999999, studentWorld, ID, startX, startY, right, 2) {};
    virtual ~Poison(){};
    virtual bool poisonous() {return true;}
    virtual void doSomething();
};

class Water: public Poison
{
public:
    Water(StudentWorld* studentWorld, int startX, int startY)
    :Poison(studentWorld, startX, startY, IID_WATER_POOL) {};
    virtual ~Water(){};
    virtual void doSomething();
};


class Pebble: public Actor
{
public:
    Pebble(StudentWorld* studentWorld, int X, int Y)
    : Actor(999999, studentWorld, IID_ROCK, X, Y, none, 1) {};
    virtual void doSomething() {};
    virtual bool blockInsect() {return true;}
};

#endif // ACTOR_H_
