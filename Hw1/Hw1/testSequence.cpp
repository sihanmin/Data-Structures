//
//  testSequence.cpp
//  Hw1
//
//  Created by Mint MSH on 1/23/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "Sequence.h"
#include <cassert>
using namespace std;

int main()
{

    Sequence t1;
    string a;
    assert(t1.empty() == true);
    assert(t1.size() == 0);
    assert(t1.insert(3,"hahaha") == false);
    assert(t1.insert(0,"hk") == true);
    assert(t1.insert("apple") == 0);
    assert(t1.insert("sss") == 2);
    assert(t1.size() == 3);
    assert(t1.insert(1,"ppap") == true);
    assert(t1.erase(10) == false);
    assert(t1.erase(1) == true);
    assert(t1.get(1,a) == true && a == "hk");
    assert(t1.insert(a) == 1);
    assert(t1.remove(a) == 2 && t1.size() == 2);
    assert(t1.insert(4,"blah") == false);
    assert(t1.insert("blah") == 1);
    assert(t1.insert("you") == 3);
    assert(t1.set(2,"mushroom") == true);
    assert(t1.insert (1,"you") == true);
    assert(t1.find("you") == 1);
    assert(t1.find("I") == -1);
    //apple you blah mushroom you
    
    Sequence t2;
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    assert(t2.insert("now") == 0);
    //now now now now now now now now
    
    t1.swap(t2);
    assert(t1.size() == 8);
    assert(t2.get(3,a) == true && a == "mushroom");
    assert(t2.get(6,a) == false);
    assert(t1.remove("now") == 8);
    
    
}

