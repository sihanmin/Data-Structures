//
//  testnewSequence.cpp
//  Hw1
//
//  Created by Mint MSH on 1/23/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "newSequence.h"
#include <cassert>
using namespace std;

int main()
{
    Sequence t1(5);
    Sequence t2;
    
    assert(t1.empty() == true);
    assert(t1.insert(7,99) == false);
    assert(t1.insert(82) == 0);
    assert(t1.insert(1,52) == true);
    assert(t1.insert(0,3) == true);
    assert(t1.insert(37) == 1);
    assert(t1.insert(96) == 4);
    assert(t1.insert(5) == -1);
    assert(t1.insert(3,7) == false);
    //3 37 82 52 96
    
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.insert(88) == 0);
    assert(t2.set(5,17) == true);
    assert(t2.remove(88) == 7);
    //17
    
    t1.swap(t2);
    assert(t1.size() == 1 && t2.size() == 5);
    assert(t2.insert(46) == -1);
    assert(t2.find(3) == 0);
    //17
    //3 37 82 52 96
    
    Sequence t3 = t2;
    assert(t3.size() == 5);
    assert(t3.insert(46) == -1);
    assert(t3.find(82) == 2);
    //3 37 82 52 96
    
    t1 = t2;
    assert(t1.size() == 5);
    assert(t1.insert(46) == -1);
    assert(t1.find(96) == 4);
    //3 37 82 52 96
    
    t3 = t3 = t2;
    assert(t3.size() == 5);
    assert(t3.insert(46) == -1);
    assert(t3.find(37) == 1);
    //3 37 82 52 96
    
}
