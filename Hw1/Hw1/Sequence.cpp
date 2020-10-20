//
//  Sequence.cpp
//  Hw1
//
//  Created by Mint MSH on 1/20/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include "Sequence.h"
using namespace std;

Sequence::Sequence()
{
    m_size = 0;
}

bool Sequence::empty() const
{
    return m_size == 0;
}

int Sequence::size() const
{
    return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
    if (checkPos(pos) == false)
        return false;
    
    for (int i = m_size; i > pos; i--)
        m_sequence[i] = m_sequence[i-1];
    m_sequence[pos] = value;
    m_size++;
    
    return true;
}

int Sequence::insert(const ItemType& value)
{
    if (checkPos(0) == false)
        return -1;
    
    int pos = m_size;
    
    for (int i = 0; i < m_size; i++)
        if (value <= m_sequence[i])
        {
            pos = i;
            break;
        }
    
    for (int i = m_size; i > pos; i--)
        m_sequence[i] = m_sequence[i-1];
    m_sequence[pos] = value;
    m_size++;
    
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    for (int i = pos; i < m_size-1; i++)
        m_sequence[i] = m_sequence[i+1];
    m_size--;
    
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int num = 0;
    
    for (int i = 0; i < m_size; i++)
    {
        if (value == m_sequence[i])
        {
            num++;
            this->erase(i);
            i--;
        }
    }
    
    return num;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    value = m_sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    m_sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    for (int i = 0; i < m_size; i++)
        if (value == m_sequence[i])
            return i;
    
    return -1;
}

void Sequence::swap(Sequence& other)
{
    ItemType temp[DEFAULT_MAX_ITEMS];
    int temp_size = 0;
    
    for (int i = 0; i < other.m_size; i++)
    {
        temp[i] = other.m_sequence[i];
    }
    temp_size = other.m_size;
    
    for (int i = 0; i < m_size; i++)
    {
        other.m_sequence[i] = m_sequence[i];
    }
    other.m_size = m_size;
    
    for (int i = 0; i < temp_size; i++)
    {
        m_sequence[i] = temp[i];
    }
    m_size = temp_size;
    
}

bool Sequence::checkPos(int pos)
{
    if (pos < 0 || pos > m_size || m_size == DEFAULT_MAX_ITEMS)
        return false;
    else
        return true;
}
