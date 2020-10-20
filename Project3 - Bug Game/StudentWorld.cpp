#include "StudentWorld.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


bool StudentWorld::canGo(int x, int y)    //can go to this block then go
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return false;
    
    std::list<Actor*>* temp;
    temp = &graph[x+y*64][1];
    for (std::list<Actor*>::iterator i = temp->begin(); i != temp->end(); i++)
    {
        if ((*i)->blockInsect() == true)
            return false;
    }
    return true;
}

bool StudentWorld::bite(int x, int y, Actor* except, int amount)
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return false;
    
    std::list<Actor*>* bugs = &graph[x+y*64][0];
    std::list<Actor*> enemies;
    int total;
    int randomBite;    // random insect among enemies
    if (bugs->size() == 1)  //make sure there is enemy in this square
        return false;
    
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i) != except)
        {
            if (amount == 50)
                enemies.push_back(*i);
            else if (amount == 15 && except->checkColony() != (*i)->checkColony() && (*i)->getEndurance() > 0)  // make sure it is alive
                enemies.push_back(*i);
        }
    }   // find all the enemies
    
    total = enemies.size(); // total number of all the potential enemies
    if (total == 0)
        return false;
    
    randomBite = randInt(1, total);
    std::list<Actor*>::iterator i = enemies.begin();
    for (int j = 1; j < randomBite; j++)
    {
        i++;    // found the one to bite in the list
    }
    (*i)->updateEndurence(amount*(-1));
    (*i)->biteBack();   // adultgrasshopper will have a chance to bite back
    (*i)->updateStatus('b');    // record bitten
    //cout << x << " " << y << " bite!!" << endl;
    return true;
}

void StudentWorld::stun(int x, int y)
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return;
    std::list<Actor*>* bugs = &graph[x+y*64][0];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if (!(*i)->checkStatus('s'))
        {
            (*i)->updateTurn(2);
            (*i)->updateStatus('s');
        }
    }
}

void StudentWorld::poison(int x, int y)
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return;
    
    std::list<Actor*>* bugs = &graph[x+y*64][0];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i)->canBePoisoned() && (*i)->checkStatus('p') == false)
        {
            (*i)->updateEndurence(-150);
            (*i)->updateStatus('p');
        }
    }
}


void StudentWorld::addAdultGrasshopper(int x, int y)
{
    //    Actor* newAdult = new AdultGrasshopper(this, x, y);
    graph[x+y*64][0].push_front(new AdultGrasshopper(this, x, y));
}

void StudentWorld::addNewAnt(int x, int y, Compiler* compiler, int ID, int colony)
{
    graph[x+y*64][0].push_back(new Ant(compiler, colony, this, ID, x, y));
    m_antNum[colony]++;
}

void StudentWorld::addPheromone(int x, int y, int colony)
{
    if ( x < 1 || x > 63 || y < 1 || y > 63)
        return;
    if (colony < 0 || colony > 3)
        return;
    
    std::list<Actor*>* bugs = &graph[x+y*64][1];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i)->checkColony() == colony)
        {
            if ((*i)->getEndurance() + 256 <= 768)
                (*i)->updateEndurence(256);
            else
                (*i)->updateEndurence(768 - (*i)->getEndurance());
            return;
        }
    }
    int imageID;
    switch (colony)
    {
        case 0:
            imageID = IID_PHEROMONE_TYPE0;
            break;
        case 1:
            imageID = IID_PHEROMONE_TYPE1;
            break;
        case 2:
            imageID = IID_PHEROMONE_TYPE2;
            break;
        case 3:
            imageID = IID_PHEROMONE_TYPE3;
            break;
        default:
            break;
    }
    bugs->push_back(new Pheromone(this, imageID, x, y, colony));
}


bool StudentWorld::hasFood(int x, int y, std::list<Actor*>::iterator &it)
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return false;
    
    std::list<Actor*>* bugs = &graph[x+y*64][1];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i)->isFood() == true && (*i)->getEndurance() > 0)
        {
            it = i;
            return true;
        }
    }
    return false;
}

int StudentWorld::pickFood(int x, int y, int amount)
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return 0;
    
    int picked = 0;
    std::list<Actor*>* bugs = &graph[x+y*64][1];
    std::list<Actor*>::iterator i = bugs->end();
    
    if (hasFood(x, y, i))
    {
        if ((*i)->getEndurance() >= amount)
            picked = amount;
        else
            picked = (*i)->getEndurance();
        (*i)->updateEndurence(picked*(-1));
    }
    return picked;
}

void StudentWorld::dropFood(int x, int y, int amount)
{
    if( x < 1 || x > 63 || y < 1 || y > 63)
        return;
    
    std::list<Actor*>* bugs = &graph[x+y*64][1];
    std::list<Actor*>::iterator i = bugs->end();
    if (hasFood(x, y, i))
    {
        (*i)->updateEndurence(amount);  // drop food in the existing food item
        return;
    }
    bugs->push_back(new Food(amount, this, x, y));
    
}

void StudentWorld::updateAnt(int x, int y, int colony)
{
    std::list<Actor*>* cur = &graph[x+64*y][0]; // current processing list
    Actor* temp;
    int newX, newY;
    std::list<Actor*>::iterator i = cur->begin();
    while (i != cur->end())
    {
        newX = (*i)->getX();
        newY = (*i)->getY();
        
        if ((*i)->checkColony() == colony && (newX != x || newY != y))  // not ant
        {
            (*i)->clearStatus();
            temp = *i;  // store the address of the actor
            graph[newX+newY*64][0].push_back(temp); //move it to its new place in graph
            i = cur->erase(i);
            return; // only one ant is moving when this function is called
        }
        i++;
    }
}


bool StudentWorld::hasEnemy(int x, int y, int colony)
{
    if ( x < 1 || x > 63 || y < 1 || y > 63)
        return false;
    if (colony < 0 || colony > 3)
        return false;
    
    std::list<Actor*>* bugs = &graph[x+y*64][0];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i)->checkColony() != colony)
        {
            return true;
        }
    }
    return false;
}

bool StudentWorld::findPheromone(int x, int y, int colony)
{
    if ( x < 1 || x > 63 || y < 1 || y > 63)
        return false;
    if (colony < 0 || colony > 3)
        return false;
    
    std::list<Actor*>* bugs = &graph[x+y*64][1];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i)->checkColony() == colony)
        {
            return true;
        }
    }
    return false;
}

bool StudentWorld::danger(int x, int y, int colony)
{
    if ( x < 1 || x > 63 || y < 1 || y > 63)
        return false;
    if (colony < 0 || colony > 3)
        return false;
    
    if (hasEnemy(x, y, colony))
        return true;
    
    std::list<Actor*>* bugs = &graph[x+y*64][1];
    for(std::list<Actor*>::iterator i = bugs->begin(); i != bugs->end(); i++)
    {
        if ((*i)->poisonous() == true)
        {
            return true;
        }
    }
    return false;
}

void StudentWorld::updateDisplayText()
{
    int max = m_antNum[m_winner];
    for (int i = 0; i < 4; i++)
    {
        if (m_antNum[i] > max)
            m_winner = i;
    }
    
    std::string temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = m_bugName[i];
    }
    temp[m_winner] += '*';
    
    ostringstream Display;
    Display << "Ticks:" << setw(5) << m_tick << " -";
    for (int i = 0; i < 4 ; i++)
    {
        Display.fill('0');
        Display << "  " << temp[i] << ": " << setw(2) << m_antNum[i];
    }
    // Create a string from your statistics, of the form:
    // Ticks: 1134 - AmyAnt: 32 BillyAnt: 33 SuzieAnt*: 77 IgorAnt: 05
    
    // Finally, update the display text at the top of the screen with your
    // newly created stats
    string s = Display.str();
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}

int StudentWorld::loadField()
{
    Field f;
    string fieldFile = getFieldFilename();
    
    string error;
    if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
    {
        setError(fieldFile + " " + error);
        return GWSTATUS_LEVEL_ERROR; // something bad happened!
    }
    // otherwise the load was successful and you can access the
    // contents of the field – here’s an example
    
    std::vector<std::string> fileNames = getFilenamesOfAntPrograms();
    m_players = fileNames.size();
    
    
    for(int i = 0; i < m_players; i++)
    {
        m_compiler[i] = new Compiler;
        // compile the source file… If the compile function returns
        // false, there was a syntax error during compilation!
        if ( ! m_compiler[i]->compile(fileNames[i], error) )
        {
            // entrant 0’s source code had a syntax error!
            // send this error to our framework to warn the user.
            // do it JUST like this!
            setError(fileNames[i] + " " + error);
            // return an error to tell our simulation framework
            // that something went wrong, and it’ll inform the user
            return GWSTATUS_LEVEL_ERROR;
        }
    }
    
    
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            Field::FieldItem item = f.getContentsOf(x,y); // note it’s x,y and not y,x!!!
            
            switch (item)   // insect into 1; others into 0
            {
                case Field::FieldItem::rock:
                    graph[x+y*64][1].push_back(new Pebble(this, x, y));
                    break;
                case Field::FieldItem::food:
                    graph[x+y*64][1].push_back(new Food(6000, this, x, y));
                    break;
                case Field::FieldItem::poison:
                    graph[x+y*64][1].push_back(new Poison(this, x, y));
                    break;
                case Field::FieldItem::water:
                    graph[x+y*64][1].push_back(new Water(this, x, y));
                    break;
                case Field::FieldItem::grasshopper:
                    graph[x+y*64][0].push_back(new BabyGrasshopper(this, x, y));
                    break;
                case Field::FieldItem::anthill0:
                    if (m_players >= 1)
                    {
                        graph[x+y*64][1].push_back(new Anthill(m_compiler[0], 0, this, x, y));  // anthill can't be bitten or anything, it behaves more like an object that produces ants
                        m_bugName[0] = m_compiler[0]->getColonyName();
                    }
                    else
                        m_bugName[0] = "-----";
                    break;
                case Field::FieldItem::anthill1:
                    if (m_players >= 2)
                    {
                        graph[x+y*64][1].push_back(new Anthill(m_compiler[1], 1, this, x, y));
                        m_bugName[1] = m_compiler[1]->getColonyName();
                    }
                    else
                        m_bugName[1] = "-----";
                    break;
                case Field::FieldItem::anthill2:
                    if (m_players >= 3)
                    {
                        graph[x+y*64][1].push_back(new Anthill(m_compiler[2], 2, this, x, y));
                        m_bugName[2] = m_compiler[2]->getColonyName();
                    }
                    else
                        m_bugName[2] = "-----";
                    break;
                case Field::FieldItem::anthill3:
                    if (m_players >= 4)
                    {
                        graph[x+y*64][1].push_back(new Anthill(m_compiler[3], 3, this, x, y));
                        m_bugName[3] = m_compiler[3]->getColonyName();
                    }
                    else
                        m_bugName[3] = "-----";
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}


void StudentWorld::moveThisList(std::list<Actor*> &cur)
{
    for (std::list<Actor*>::iterator i = cur.begin(); i != cur.end(); i++)
    {
        // get the actor’s current location
        if ((*i)->getEndurance() > 0 && (*i)->complete() == false)
        {
            (*i)->doSomething();
        }
    }
}

void StudentWorld::update(int x, int y, int c)
{
    if (c != 1 && c!= 0)
        return;
    
    std::list<Actor*>* cur = &graph[x+64*y][c]; // current processing list
    Actor* temp;
    int newX, newY;
    std::list<Actor*>::iterator i = cur->begin();
    while (i != cur->end())
    {
        if ((*i)->getEndurance() <= 0)
        {
            //            if (c == 0 && (*i)->checkColony() != -1)
            //            {
            //                m_antNum[(*i)->checkColony()]--;
            //            }   // erase the dead ant from the antNum
            //
            if ((*i)->deadDropFood())
                dropFood(x, y, 100);    // replace the dead body
            delete (*i);
            i = cur->erase(i);  //remove
            //cout << "dead now" << endl;
            continue;
        }
        if (c == 0 && (*i)->checkColony() != -1)
            (*i)->notComplete();
        newX = (*i)->getX();
        newY = (*i)->getY();
        if (newX != x || newY != y)
        {
            (*i)->clearStatus();
            temp = *i;  // store the address of the actor
            graph[newX+newY*64][c].push_back(temp); //move it to its new place in graph
            i = cur->erase(i);
            continue;
        }
        i++;
    }
    
}

void StudentWorld::deleteList(std::list<Actor*> &cur)
{
    for (std::list<Actor*>::iterator i = cur.begin(); i != cur.end(); i++)
    {
        delete (*i);
    }
}

