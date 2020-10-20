//
//  Game.hpp
//  Project1
//
//  Created by Mint MSH on 1/12/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_hpp */
