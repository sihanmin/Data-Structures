//
//  Sequence.cpp
//  Project2
//
//  Created by Mint MSH on 1/25/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include "Sequence.h"
#include <string>
using namespace std;

Sequence::Sequence()    // Create an empty sequence (i.e., one whose size() is 0).
{
    head = nullptr;
    m_size = 0;
}

Sequence::~Sequence()
{
    deleteAll();
}

Sequence::Sequence(const Sequence &src)
{
    m_size = src.m_size;
    if (src.head == nullptr)
    {
        head = nullptr;
        return;
    }
    
    head = new Node;
    Node *p = head;
    Node *pSrc = src.head;
    Node *prev = nullptr;
    
    while (pSrc != nullptr && pSrc->next != nullptr)
    {
        p->value = pSrc->value;
        p->prev = prev;
        p->next = new Node;
        prev = p;
        p = p->next;
        pSrc = pSrc->next;
    }
    p->value = pSrc->value;
    p->prev = prev;
    p->next = nullptr;
}

Sequence& Sequence::operator=(const Sequence &src)
{
    if (this == &src || head == src.head)
        return (*this);
    
    deleteAll();
    m_size = src.m_size;
    if (src.head == nullptr)
    {
        head = nullptr;
        return (*this);
    }
    
    head = new Node;
    Node *p = head;
    Node *pSrc = src.head;
    Node *prev = nullptr;
    
    while (pSrc != nullptr && pSrc->next != nullptr)
    {
        p->value = pSrc->value;
        p->prev = prev;
        p->next = new Node;
        prev = p;
        p = p->next;
        pSrc = pSrc->next;
    }
    p->value = pSrc->value;
    p->prev = prev;
    p->next = nullptr;
    
    return (*this);
}

bool Sequence::empty() const
// Return true if the sequence is empty, otherwise false.
{
    if (m_size == 0)
        return true;
    
    return false;
}
int Sequence::size() const
{
    return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > m_size)
        return false;
    
    if (pos == 0)
    {
        addToFront(value);
        return true;
    }
    
    int curPos = 1;   //the next one of the current oneBefore pointer
    Node *oneBefore = head;
    Node *latest = new Node;
    while (curPos != pos && oneBefore != nullptr)
    {
        oneBefore = oneBefore->next;
        curPos++;
    }
    
    latest->next = oneBefore->next;
    latest->value = value;
    latest->prev = oneBefore;
    oneBefore->next = latest;
    if (latest->next != nullptr)
        latest->next->prev = latest;    //add in the middle of the link list
    m_size++;
    return true;
}

int Sequence::insert(const ItemType& value)
{
    if (head == nullptr || value <= head->value)
    {
        addToFront(value);
        return 0;
    }
    Node *oneBefore = head;
    int pos = 1;
    while (oneBefore->next != nullptr)    // value > all
    {
        if (value <= oneBefore->next->value)
            break;
        oneBefore = oneBefore->next;
        pos++;
    }
    
    Node *latest = new Node;
    latest->next = oneBefore->next;
    latest->prev = oneBefore;
    latest->value = value;
    oneBefore->next = latest;
    if (latest->next != nullptr)
        latest->next->prev = latest;
    m_size++;
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    if (pos == 0)
    {
        deleteFirst();
        return true;
    }
    
    int curPos = 1;
    Node *oneBefore = head;
    while (curPos != pos)
    {
        oneBefore = oneBefore->next;
        curPos++;
    }
    Node *deleteThis = oneBefore->next;
    oneBefore->next = deleteThis->next;
    if (deleteThis->next != nullptr)
        oneBefore->next->prev = oneBefore;
    delete deleteThis;
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    Node *p = head;
    int num = 0;
    int pos = 0;
    
    while (p != nullptr && p->value == value)
    {
        erase(pos);
        p = head;
        num++;
    }
    
    pos = 1;
    while (p != nullptr && p->next != nullptr)
    {
        if (value == p->next->value)
        {
            num++;
            erase(pos);
            continue;
        }
        p = p->next;
        pos++;
    }
    
    return num;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    Node *p = head;
    int curPos = 0;
    while (curPos != pos && p != nullptr)
    {
        curPos++;
        p = p->next;
    }
    if (p != nullptr)
        value = p->value;
    
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size)
        return false;
    
    Node *p = head;
    int curPos = 0;
    while (curPos != pos && p != nullptr)
    {
        curPos++;
        p = p->next;
    }
    if (p != nullptr)
        p->value = value;
    
    return true;
}

int Sequence::find(const ItemType& value) const
{
    Node *p = head;
    int pos = 0;
    while (p != nullptr)
    {
        if (value == p->value)
        {
            return pos;
        }
        pos++;
        p = p->next;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    Node *temp = nullptr;
    int temp_size;
    
    temp = head;
    head = other.head;
    other.head = temp;
    
    temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

void Sequence::addToFront(ItemType value)
{
    Node *p = new Node;
    p->value = value;
    p->next = head;
    p->prev = nullptr;
    if (p->next != nullptr)
        p->next->prev = p;
    head = p;
    m_size++;
}

void Sequence::deleteFirst()
{
    if (head == nullptr)
        return;
    
    Node *deleteThis = head;
    if (deleteThis->next != nullptr)
        deleteThis->next->prev = nullptr;
    head = deleteThis->next;
    delete deleteThis;
    m_size--;
}

void Sequence::deleteAll()
{
    if (head == nullptr)
        return;
    
    Node *p = head;
    Node *next = nullptr;
    while (p != nullptr & p->next != nullptr)
    {
        next = p->next;
        delete p;
        p = next;
    }
    delete p;

}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq1.size() < seq2.size() || seq2.size() == 0)
        return -1;
    
    if (&seq1 == &seq2)
        return 0;
    
    ItemType value2,value2First;
    ItemType value1;
    seq2.get(0,value2First);
    int pos1 = seq1.find(value2First);
    int pos2 = 0;
    
    if (pos1 == -1)
        return -1;
    
    while (pos1 < seq1.size())
    {
        seq1.get(pos1,value1);
        seq2.get(pos2,value2);
        if (value1 == value2)
        {
            pos1++;
            pos2++;
            if (pos2 == seq2.size())
                return pos1-pos2;
        }
        else
        {
            if (value1 == value2First)
                pos2 = 1;
            else
                pos2 = 0;
            pos1++;
        }
    }
    
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    if (seq1.size() == 0)
    {
        result = seq2;
        return;
    }
    else if (seq2.size() == 0)
    {
        result = seq1;
        return;
    }
    
    if (&result != &seq1 && &result != &seq2)
    {
        while(result.size() != 0)
            result.erase(0);
    }
    
    int pos1 = 0, pos2 = 0, posr = 0;
    Sequence temp;
    ItemType value1, value2;
    while (pos1 < seq1.size() || pos2 < seq2.size())
    {
        if (pos1 < seq1.size())
        {
            seq1.get(pos1,value1);
            temp.insert(posr, value1);
            posr++;
            pos1++;
        }
        if (pos2 < seq2.size())
        {
            seq2.get(pos2,value2);
            temp.insert(posr, value2);
            posr++;
            pos2++;
        }
    }
    result.swap(temp);
}

