//
//  testScoreList.cpp
//  Hw1
//
//  Created by Mint MSH on 1/21/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include "ScoreList.h"
#include "Sequence.h"
#include <cassert>
#include <stdio.h>
using namespace std;

int main()
{
    ScoreList c1;
    assert(c1.size() == 0);
    assert(c1.add(10) == true);
    assert(c1.add(89) == true);
    assert(c1.add(100) == true);
    assert(c1.add(-1) == false);
    assert(c1.add(200) == false);
    assert(c1.size() == 3);
    assert(c1.add(23) == true);
    assert(c1.add(77) == true);
    assert(c1.add(23) == true);
    assert(c1.add(0) == true);
    //0 10 23 23 77 89 100
    
    assert(c1.remove(9) == false);
    assert(c1.remove(23) == true);
    assert(c1.size() == 6);
    assert(c1.remove(100) == true);
    assert(c1.remove(0) == true);
    assert(c1.size() == 4);
    //10 23 77 89
    
    c1.add(53);
    c1.add(31);
    c1.add(99);
    c1.add(72);
    c1.add(64);
    assert(c1.minimum() == 10);
    assert(c1.maximum() == 99);
    //10 23 31 53 64 72 77 89 99
   
}
