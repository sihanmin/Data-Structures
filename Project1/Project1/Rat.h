//
//  Rat.hpp
//  Project1
//
//  Created by Mint MSH on 1/12/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#ifndef RAT_H
#define RAT_H

//#include "Arena.h"
///class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Rat declaration.

class Arena;

class Rat
{
public:
    // Constructor
    Rat(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif /* Rat_hpp */
