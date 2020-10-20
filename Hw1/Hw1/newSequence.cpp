//
//  newSequence.cpp
//  Hw1
//
//  Created by Mint MSH on 1/22/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include "newSequence.h"
using namespace std;


Sequence::Sequence()
{
    m_size = 0;
    m_sequence = new ItemType[DEFAULT_MAX_ITEMS];
    m_maxItems = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int maxItems)
{
    m_size = 0;
    m_sequence = new ItemType[maxItems];
    m_maxItems = maxItems;
}

Sequence::Sequence(const Sequence &src)
{
    m_size = src.m_size;
    m_maxItems = src.m_maxItems;
    m_sequence = new ItemType[m_maxItems];
    for(int i = 0; i < m_size; i++)
        m_sequence[i] = src.m_sequence[i];
}

Sequence::~Sequence()
{
    delete [] m_sequence;
}

Sequence& Sequence::operator= (const Sequence &src)
{
    if (&src == this)
        return (*this);
    
    delete [] m_sequence;
    m_size = src.m_size;
    m_maxItems = src.m_maxItems;
    m_sequence = new ItemType[m_maxItems];
    for(int i = 0; i < m_size; i++)
        m_sequence[i] = src.m_sequence[i];
    return (*this);
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
    ItemType *temp_sequence;
    temp_sequence = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = temp_sequence;
    
    int temp_size;
    temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    int temp_maxItems;
    temp_maxItems = m_maxItems;
    m_maxItems = other.m_maxItems;
    other.m_maxItems = temp_maxItems;
}

bool Sequence::checkPos(int pos)
{
    if (pos < 0 || pos > m_size || m_size == m_maxItems)
        return false;
    else
        return true;
}
