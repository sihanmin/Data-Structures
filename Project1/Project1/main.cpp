// rats.cpp
/*
#include "Arena.h"
#include "History.h"
#include "globals.h"
int main()
{
    Arena a(1, 4);
    a.addPlayer(1, 4);
    for (int t = 1; t <= 2; t++)
    {
        a.addRat(1, 1);
        a.setCellStatus(1, 2, HAS_POISON);
        a.setCellStatus(1, 3, HAS_POISON);
        while (a.ratCount() > 0)
            a.moveRats();
    }

    a.history().display();
}
*/

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include "globals.h"
#include "Rat.h"
#include "Player.h"
#include "Arena.h"
#include "Game.h"
using namespace std;


int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(20, 20, 40);
    
    // Play the game
    g.play();
}
