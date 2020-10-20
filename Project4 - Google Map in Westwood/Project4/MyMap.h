//
//  MyMap.h
//  Project4
//
//  Created by Mint MSH on 3/10/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#ifndef MyMap_h
#define MyMap_h

#include <stdio.h>
#include <iostream>

// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap();
    ~MyMap();
    void clear();
    int size() const;
    void associate(const KeyType& key, const ValueType& value);
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node
    {
        Node(const KeyType& myKey, const ValueType& myValue)
        {
            key = myKey;
            value = myValue;
            left = right = nullptr;
        }
        KeyType key;
        ValueType value;
        Node *left;
        Node *right;
    };
    Node *m_root;
    int m_size;
    
    void freeTree(Node* cur);
    Node* search(const KeyType& key) const;
};

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap()
{
    m_root = nullptr;
    m_size = 0;
}

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap()
{
    clear();
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear()
{
    freeTree(m_root);
    m_root = nullptr;
}

template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const
{
    return m_size;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    if (m_root == nullptr)
    {
        m_root = new Node(key, value);
        m_size++;
        return;
    }
    
    Node* loc = search(key);
    if (key < loc->key)
    {
        loc->left = new Node(key, value);
        m_size++;
    }
    else if (key > loc->key)
    {
        loc->right = new Node(key, value);
        m_size++;
    }
    else
        loc->value = value;

}

template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType, ValueType>::find(const KeyType& key) const
{
    if (m_root == nullptr)
        return nullptr;
    
    Node* loc = search(key);
    if (key == loc->key)
        return &(loc->value);
    else
        return nullptr;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::freeTree(Node* cur)
{
    if (cur == nullptr)
        return;
    freeTree(cur->left);
    freeTree(cur->right);
    delete cur;
    m_size--;
}

template<typename KeyType, typename ValueType>
typename MyMap<KeyType, ValueType>::Node* MyMap<KeyType, ValueType>::search(const KeyType& key) const   // return the node of key or the last node in the branch
                // assume the tree is not empty
{
    Node *cur = m_root;
    for (; ;)
    {
        if (key == cur->key)
            return cur;
        if (key < cur->key)
        {
            if (cur->left != nullptr)
                cur = cur->left;
            else
                return cur;
        }
        else if (key > cur->key)
        {
            if (cur->right != nullptr)
                cur = cur->right;
            else
                return cur;
        }
    }
}

#endif /* MyMap_hpp */
