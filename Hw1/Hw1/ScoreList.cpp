//
//  ScoreList.cpp
//  Hw1
//
//  Created by Mint MSH on 1/21/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList()
{
    
}

bool ScoreList::add(unsigned long score)
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
{
    if(score > 100)
        return false;
    
    if (m_sequence.insert(score) == -1)
        return false;
        
    return true;
}

bool ScoreList::remove(unsigned long score)
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
{
    int pos = m_sequence.find(score);
    
    if (pos == -1)
        return false;
    
    m_sequence.erase(pos);
    return true;
}

int ScoreList::size() const
// Return the number of scores in the list.
{
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
{
    if (m_sequence.size() == 0)
        return NO_SCORE;
    
    unsigned long min =  101;
    unsigned long temp = 101;
    
    for (int i = 0; i < m_sequence.size(); i++)
    {
        m_sequence.get(i,temp);
        if (min > temp)
            min = temp;
    }
    return min;
}

unsigned long ScoreList::maximum() const
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
{
    if (m_sequence.size() == 0)
        return NO_SCORE;
    
    unsigned long max =  0;
    unsigned long temp = 0;
    
    for (int i = 0; i < m_sequence.size(); i++)
    {
        m_sequence.get(i,temp);
        if (max < temp)
            max = temp;
    }
    return max;
}
