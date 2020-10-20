//
//  History.cpp
//  Project1
//
//  Created by Mint MSH on 1/13/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            m_grid[r-1][c-1] = '.';
}

bool History::record(int r, int c)
{
    if (r <= 0  ||  c <= 0  ||  r > m_rows  ||  c > m_cols)
    {
        return false;
    }
    else
    {
        if(m_grid[r-1][c-1] == '.')
            m_grid[r-1][c-1] = 'A';
        else if(m_grid[r-1][c-1] != 'Z')
            m_grid[r-1][c-1]++;
    }
    return true;
}

void History::display() const
{
    int r,c;
    
    clearScreen();
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << m_grid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
