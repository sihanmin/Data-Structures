//
//  History.hpp
//  Project1
//
//  Created by Mint MSH on 1/13/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;

private:
    char    m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    
};

#endif /* History_hpp */
