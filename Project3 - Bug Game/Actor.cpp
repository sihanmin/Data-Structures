#include "Actor.h"
#include "StudentWorld.h"
#include <sstream>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

bool Actor::checkStatus(char st)
{
    for (int i = 0; i < m_status.size(); i++)
    {
        if (m_status[i] == st)
            return true;
    }
    return false;
}

int Insect::attemptNextStep(Direction dir) // check if next step would be successful
// do it if it's not blocked    // return 1 for can go
{
    int mark = -1;
    switch (dir)
    {
        case up:
            if (getWorld()->canGo(getX(), getY()+1))
            {
                moveTo(getX(), getY()+1);
                mark = 1;
            }
            break;
        case right:
            if (getWorld()->canGo(getX()+1, getY()))
            {
                moveTo(getX()+1, getY());
                mark = 1;
            }
            break;
        case down:
            if (getWorld()->canGo(getX(), getY()-1))
            {
                moveTo(getX(), getY()-1);
                mark = 1;
            }
            break;
        case left:
            if (getWorld()->canGo(getX()-1, getY()))
            {
                moveTo(getX()-1, getY());
                mark = 1;
            }
            break;
        default:
            break;
    }
    if (mark == -1)
        updateStatus('l');
    return mark;
}


int Ant::toNum(string s)
{
    stringstream a;
    int i;
    a << s;
    a >> i;
    return i;
}

void Ant::moveTheAntForward()
{
    attemptNextStep(getDirection());
    // more to do!!
}

void Ant::pickupSomeFood()
{
    int couldPick = 1800 - m_food;
    if (couldPick >= 400)
        m_food += getWorld()->pickFood(getX(), getY(), 400);
    else
        m_food += getWorld()->pickFood(getX(), getY(), couldPick);
}

void Ant::dropSomeFood()
{
    getWorld()->dropFood(getX(), getY(), m_food);
}

void Ant::eatSomeFood()
{
    if (m_food >= 100)
    {
        m_food -= 100;
        updateEndurence(100);
    }
    else
    {
        updateEndurence(m_food);
        m_food = 0;
    }
}

void Ant::bite()
{
    getWorld()->bite(getX(), getY(), this, 15);
}

void Ant::rotateClockwise()
{
    switch (getDirection())
    {
        case up:
            setDirection(right);
            break;
        case right:
            setDirection(down);
            break;
        case down:
            setDirection(left);
            break;
        case left:
            setDirection(up);
            break;
        default:
            break;
    }
}

void Ant::rotateCounterClockwise()
{
    switch (getDirection())
    {
        case up:
            setDirection(left);
            break;
        case right:
            setDirection(up);
            break;
        case down:
            setDirection(right);
            break;
        case left:
            setDirection(down);
            break;
        default:
            break;
    }
}

void Ant::faceRandomDirection()
{
    int dir = randInt(1, 4);
    switch (dir)
    {
        case 1: setDirection(up); break;
        case 2: setDirection(right); break;
        case 3: setDirection(down); break;
        case 4: setDirection(left); break;
    }
}

void Ant::generateRandomNumber(int N)
{
    m_lastRandom = randInt(0, N-1);
}

void Ant::emitPheromone()
{
    getWorld()->addPheromone(getX(), getY(), m_colony);
}

bool Ant::checkInFront(std::string check)
{
    if (check != "pheronmone" && check != "danger")
        return false;
    
    switch (getDirection())
    {
        case up:
            if (check == "pheronmone" && getWorld()->findPheromone(getX(), getY()+1, m_colony))
                return true;
            if (check == "danger" && getWorld()->danger(getX(), getY()+1, m_colony))
                return true;
            break;
        case right:
            if (check == "pheronmone" && getWorld()->findPheromone(getX()+1, getY(), m_colony))
                return true;
            if (check == "danger" && getWorld()->danger(getX()+1, getY(), m_colony))
                return true;
            break;
        case down:
            if (check == "pheronmone" && getWorld()->findPheromone(getX(), getY()-1, m_colony))
                return true;
            if (check == "danger" && getWorld()->danger(getX(), getY()-1, m_colony))
                return true;
            break;
        case left:
            if (check == "pheronmone" && getWorld()->findPheromone(getX()-1, getY(), m_colony))
                return true;
            if (check == "danger" && getWorld()->danger(getX()-1, getY(), m_colony))
                return true;
            break;
        default:
            break;
    }
    return false;
}

bool Ant::conditionTrue(int statement)
{
    std::list<Actor*>::iterator it; // for check food function
    switch (statement)
    {
        case Compiler::last_random_number_was_zero:
            return (m_lastRandom == 0);
        case Compiler::i_am_carrying_food:
            return (m_food > 0);
        case Compiler::i_am_hungry:
            return (getEndurance() <= 25);
        case Compiler::i_am_standing_with_an_enemy:
            return (getWorld()->hasEnemy(getX(), getY(), m_colony));
        case Compiler::i_am_standing_on_food:
            return (getWorld()->hasFood(getX(), getY(), it));
        case Compiler::i_am_standing_on_my_anthill:
            return (getX() == m_momX && getY() == m_momY);
        case Compiler::i_smell_pheromone_in_front_of_me:
            return checkInFront("pheromone");
        case Compiler::i_smell_danger_in_front_of_me:
            return checkInFront("danger");
        case Compiler::i_was_bit:
            return checkStatus('b');
        case Compiler::i_was_blocked_from_moving:
            return checkStatus('l');
        default:
            break;
    }
    return false;
}

bool Ant::interpreter()
{
    Compiler::Command cmd;
    
    // get the command from element ic of the vector
    if ( ! m_compiler->getCommand(m_ic, cmd) )
        return false; // error - no such instruction!
    
    int operand1 = toNum(cmd.operand1);
    int operand2 = toNum(cmd.operand2);
    
    switch (cmd.opcode)
    {
        case Compiler::moveForward:
            // cause the ant to move forward by
            // updating its x,y coordinates
            if (attemptNextStep(getDirection()) == 1)
                getWorld()->updateAnt(getX(), getY(), m_colony);
            ++m_ic; // advance to next instruction
            break;
        case Compiler::pickupFood:
            pickupSomeFood();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::dropFood:
            dropSomeFood();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::eatFood:
            eatSomeFood();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::bite:
            bite();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::rotateClockwise:
            rotateClockwise();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::rotateCounterClockwise:
            rotateCounterClockwise();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::faceRandomDirection:
            faceRandomDirection();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::generateRandomNumber:
            generateRandomNumber(operand1);
            ++m_ic; // advance to next instruction
            break;
        case Compiler::emitPheromone:
            emitPheromone();
            ++m_ic; // advance to next instruction
            break;
        case Compiler::if_command:
            // if the condition of the if command is
            // is true, then go to the target position
            // in the vector; otherwise fall through to
            // the next position
            if (conditionTrue(operand1))
                m_ic = operand2;
            else
                ++m_ic; // just advance to the next line
            break;
        case Compiler::goto_command:
            // just set ic the specified position
            // in operand1
            m_ic = operand1;
            break;
    }
    return true;
}

void Ant::doSomething()
{
    updateEndurence(-1);
    if (getEndurance() <= 0)
        return;
    
    if (getTurn() > 0)
    {
        updateTurn(-1);
        return;
    }
    
    m_ic = 0;
    for (int i = 0; i < 10; i++)
    {
        if (!interpreter())
        {
            updateEndurence(getEndurance()*(-1));
            return;
        }
        if (getEndurance() <= 0)
            return;
    }
    m_complete = true;
}

void Grasshopper::pickNewWay()
{
    updateDis(randInt(2, 10));
    int dir = randInt(1, 4);
    switch (dir)
    {
        case 1: setDirection(up); break;
        case 2: setDirection(right); break;
        case 3: setDirection(down); break;
        case 4: setDirection(left); break;
    }   // copied code from constructor
}

void BabyGrasshopper::doSomething()
{
    updateEndurence(-1);
    if (getEndurance() <= 0)
        return;
    
    if (getTurn() > 0)
    {
        updateTurn(-1);
        return;
    }
    
    if (getEndurance() >= 1600)
    {
        int endurance = getEndurance();
        updateEndurence(endurance*(-1));
        getWorld()->addAdultGrasshopper(getX(), getY());
        return;
    }
    
    int foodPicked = getWorld()->pickFood(getX(), getY(), 200);
    updateEndurence(foodPicked);
    if (foodPicked > 0 && randInt(1, 2) == 1)
    {
        updateTurn(2);
        return;
    }
    
    if (getDis() == 0)
        pickNewWay();
    
    
    if (attemptNextStep(getDirection()) == -1)    // if fail next step
    {
        int dis = getDis();
        updateDis(dis*(-1));
    }
    else
    {
        updateDis(-1);
    }
    updateTurn(2);
}

void AdultGrasshopper::biteBack()
{
    int bite = randInt(1, 2);
    if (bite == 1)
        getWorld()->bite(getX(), getY(), this, 50);
}


void AdultGrasshopper::doSomething()
{
    updateEndurence(-1);
    if (getEndurance() <= 0)
        return;
    
    if (getTurn() > 0)
    {
        updateTurn(-1);
        return;
    }
    
    
    bool finished =  false;
    
    if (randInt(1, 3) == 1)  // check if bite this round
    {
        if (getWorld()->bite(getX(), getY(), this, 50) == true)
            finished = true;
    }
    
    if (randInt(1, 10) == 1 && !finished)
    {
        int mark  = 0;
        int time = 0;
        do
        {
            time++;
            int changeX, changeY, maxY;
            changeX = randInt(-10, 10);
            maxY = sqrt(100-changeX*changeX);   // the border of radius 10 for Y
            changeY = randInt((-1)*maxY, maxY);
            int newX = getX()+changeX;
            int newY = getY()+changeY;
            if (getWorld()->canGo(newX, newY))
            {
                moveTo(newX, newY);
                mark = 1;
            }
        }while (mark == 0 && time < 2000);  // if fail 2000 times, just give up
    }
    
    int foodPicked;
    if (!finished)
    {
        foodPicked = getWorld()->pickFood(getX(), getY(), 200);
        updateEndurence(foodPicked);
        if (foodPicked > 0 && randInt(1, 2) == 1)
            finished = true;
    }
    
    if (finished)   // check if the grasshopper has finished this tick
    {
        updateTurn(2);
        return;
    }
    
    if (getDis() == 0)
        pickNewWay();
    
    if (attemptNextStep(getDirection()) == -1)    // if fail next step
    {
        int dis = getDis();
        updateDis(dis*(-1));
    }
    else
    {
        updateDis(-1);
    }
    updateTurn(2);
}

void Anthill::doSomething()
{
    updateEndurence(-1);
    int endurance = getEndurance();
    
    if (endurance <= 0)
        return;
    
    int foodPicked = getWorld ()->pickFood(getX(), getY(), 100000);   // eat available
    updateEndurence(foodPicked);
    if (foodPicked > 0)
        return;
    
    if (endurance >= 2000)
    {
        int ID;
        switch (m_colony)
        {
            case 0:
                ID = IID_ANT_TYPE0;
                break;
            case 1:
                ID = IID_ANT_TYPE1;
                break;
            case 2:
                ID = IID_ANT_TYPE2;
                break;
            case 3:
                ID = IID_ANT_TYPE3;
                break;
            default:
                break;
        }
        getWorld()->addNewAnt(getX(), getY(), m_compiler, ID, m_colony);
        updateEndurence(-1500);
        //cout << "ant NO. " << m_ants << endl;
    }
}

void Poison::doSomething()
{
    getWorld()->poison(getX(), getY());
}

void Water::doSomething()
{
    getWorld()->stun(getX(), getY());
}

