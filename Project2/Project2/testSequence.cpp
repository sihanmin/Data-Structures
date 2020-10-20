////
////  main.cpp
////  Project2
////
////  Created by Mint MSH on 1/25/17.
////  Copyright © 2017 Mint MSH. All rights reserved.
////
//
//#include <iostream>
//#include "Sequence.h"
//#include <string>
//#include <cassert>
//using namespace std;
//
//int main() {
//    Sequence t1;
//    string a;
//    assert(t1.empty() == true);
//    assert(t1.size() == 0);
//    assert(t1.insert("apple") == 0);
//    assert(t1.erase(0) == true);
//    assert(t1.insert(3,"hahaha") == false);
//    assert(t1.insert(0,"hk") == true);
//    assert(t1.insert("apple") == 0);
//    assert(t1.insert("sss") == 2);
//    assert(t1.size() == 3);
//    assert(t1.insert(1,"ppap") == true);
//    assert(t1.erase(10) == false);
//    assert(t1.erase(1) == true);
//    assert(t1.get(1,a) == true && a == "hk");
//    assert(t1.insert(a) == 1);
//    assert(t1.remove(a) == 2 && t1.size() == 2);
//    assert(t1.insert(4,"blah") == false);
//    assert(t1.insert("blah") == 1);
//    assert(t1.insert("you") == 3);
//    assert(t1.set(2,"mushroom") == true);
//    assert(t1.insert("apple") == 0);
//    assert(t1.insert("apple") == 0);
//    assert(t1.remove("apple") == 3);
//    assert(t1.insert("apple") == 0);
//    assert(t1.insert (1,"you") == true);
//    assert(t1.find("you") == 1);
//    assert(t1.find("I") == -1);
//    //apple you blah mushroom you
//    
//    Sequence t2;
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    assert(t2.insert("now") == 0);
//    //now now now now now now now now
//    
////    t1.swap(t2);
////    assert(t1.size() == 8);
////    assert(t2.get(3,a) == true && a == "mushroom");
////    assert(t2.get(6,a) == false);
////    assert(t1.remove("now") == 8);
//    
//    Sequence t3;
//    assert(subsequence(t1, t2) == -1);
//    assert(t2.remove("now") == 8);
//    interleave(t1, t2, t3);
//   
//    t2.insert("blah");
//    assert(subsequence(t1, t2) == 2);
//    t2.insert("mushroom");
//    assert(subsequence(t1, t2) == 2);
//    t2.insert(0, "you");
//    assert(subsequence(t1, t2) == 1);
//    t1.insert("you");
//    assert(subsequence(t1, t2) == 2);
//    
//    t1.swap(t2);
//    assert(subsequence(t1, t2) == -1);
//    t2.erase(0);
//    t2.erase(0);
//    assert(subsequence(t1, t2) == -1);   //you blah mushroom    //you blah mushroom you
//    t1.erase(0);
//    
//
//    interleave(t1, t2, t3);
//    t1.swap(t2);
//    interleave(t1, t2, t3);
//    
//    cout << "pass all test" << endl;
//
//    
//    
//}
