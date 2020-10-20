//
//  Player.hpp
//  Project1
//
//  Created by Mint MSH on 1/12/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
//#include <string>

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    std::string dropPoisonPellet();
    std::string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* Player_hpp */
