////
////  main.cpp
////  Project2
////
////  Created by Mint MSH on 1/25/17.
////  Copyright © 2017 Mint MSH. All rights reserved.
////

#include "OurType.h"
#include "Sequence.h"
#include <iostream>
#include <cstdlib>
#include <type_traits>
#include <cassert>

using namespace std;

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
    return OurType::m_count;
}

inline int nasstcopys()
{
    return OurType::m_asstcopycount;
}

ItemType SOMEVAL = ItemType(123);
ItemType DEFAULT = ItemType(0);
ItemType ARRAY[6] = {
    ItemType(10), ItemType(20), ItemType(30),
    ItemType(40), ItemType(50), ItemType(60),
};

void testone(int n)
{
    Sequence s;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Sequence::empty), bool (Sequence::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Sequence::size), int (Sequence::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Sequence::get), bool (Sequence::*)(int, OurType&) const>::value));
        } break; case  4: {
            assert((is_same<decltype(&Sequence::find), int (Sequence::*)(const OurType&) const>::value));
        } break; case  5: {
            assert(s.empty());
        } break; case  6: {
            assert(s.size() == 0);
        } break; case  7: {
            assert(!s.erase(0)  &&  s.size() == 0);
        } break; case  8: {
            assert(s.remove(DEFAULT) == 0  &&  s.size() == 0);
        } break; case  9: {
            OurType x = SOMEVAL;
            assert(!s.get(0, x));
        } break; case 10: {
            OurType x = SOMEVAL;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 11: {
            assert(!s.set(0, SOMEVAL)  &&  s.size() == 0);
        } break; case 12: {
            assert(s.find(DEFAULT) == -1);
        } break; case 13: {
            assert(s.insert(0,SOMEVAL));
        } break; case 14: {
            s.insert(0,SOMEVAL);
            assert(! s.empty());
        } break; case 15: {
            s.insert(0,SOMEVAL);
            assert(s.size() == 1);
        } break; case 16: {
            s.insert(0,SOMEVAL);
            assert(s.find(SOMEVAL) == 0);
        } break; case 17: {
            s.insert(0,SOMEVAL);
            OurType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 18: {
            s.insert(0,SOMEVAL);
            OurType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 19: {
            s.insert(0,SOMEVAL);
            assert(s.set(0, DEFAULT));
        } break; case 20: {
            s.insert(0,SOMEVAL);
            s.set(0, DEFAULT);
            assert(s.size() == 1);
            OurType x = SOMEVAL;
            s.get(0, x);
            assert(x == DEFAULT);
        } break; case 21: {
            s.insert(0,DEFAULT);
            s.set(0, SOMEVAL);
            assert(s.size() == 1);
            OurType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 22: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            assert(! s.empty()   &&  s.size() == 2);
        } break; case 23: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            OurType x = SOMEVAL;
            s.get(0,x);
            assert(x == ARRAY[0]);
        } break; case 24: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            OurType x = SOMEVAL;
            s.get(1,x);
            assert(x == ARRAY[1]);
        } break; case 25: {
            s.insert(0, ARRAY[0]);
            s.insert(0, ARRAY[1]);
            assert(s.size() == 2);
        } break; case 26: {
            s.insert(0, ARRAY[0]);
            s.insert(0, ARRAY[1]);
            OurType x = SOMEVAL;
            s.get(0,x);
            assert(x == ARRAY[1]);
        } break; case 27: {
            s.insert(0, ARRAY[0]);
            s.insert(0, ARRAY[1]);
            OurType x = SOMEVAL;
            s.get(1,x);
            assert(x == ARRAY[0]);
        } break; case 28: {
            s.insert(0, ARRAY[3]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[0]);
            s.insert(0, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            assert(s.size() == 5);
        } break; case 29: {
            s.insert(0, ARRAY[3]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[0]);
            s.insert(0, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            for (size_t k = 0; k < 5; k++)
            {
                OurType x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[5-1-k]);
            }
        } break; case 30: {
            s.insert(0, ARRAY[3]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[0]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            for (size_t k = 0; k < 5; k++)
                s.set(k, ARRAY[k]);
            assert(s.size() == 5);
            for (size_t k = 0; k < 5; k++)
            {
                OurType x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 31: {
            assert(s.insert(SOMEVAL) == 0);
        } break; case 32: {
            s.insert(SOMEVAL);
            assert(! s.empty());
        } break; case 33: {
            s.insert(SOMEVAL);
            assert(s.size() == 1);
        } break; case 34: {
            s.insert(SOMEVAL);
            assert(s.find(SOMEVAL) == 0);
        } break; case 35: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            assert(! s.empty()   &&  s.size() == 2);
        } break; case 36: {
            s.insert(SOMEVAL);
            OurType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 37: {
            s.insert(SOMEVAL);
            OurType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 38: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            OurType x = SOMEVAL;
            s.get(0,x);
            assert(x == ARRAY[0]);
        } break; case 39: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            OurType x = SOMEVAL;
            s.get(1,x);
            assert(x == ARRAY[1]);
        } break; case 40: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            OurType x = SOMEVAL;
            s.get(0,x);
            assert(x == ARRAY[0]);
        } break; case 41: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            OurType x = SOMEVAL;
            s.get(1,x);
            assert(x == ARRAY[1]);
        } break; case 42: {
            assert(s.insert(ARRAY[3]) == 0);
            assert(s.insert(ARRAY[1]) == 0);
            assert(s.insert(ARRAY[0]) == 0);
            assert(s.insert(ARRAY[4]) == 3);
            assert(s.insert(ARRAY[2]) == 2);
            assert(s.size() == 5);
        } break; case 43: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            for (size_t k = 0; k < 5; k++)
            {
                OurType x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 44: {
            assert(s.insert(ARRAY[2]) == 0);
            assert(s.insert(ARRAY[1]) == 0);
            assert(s.insert(ARRAY[0]) == 0);
            assert(s.insert(ARRAY[1]) == 1);
            assert(s.insert(ARRAY[1]) == 1);
            assert(s.size() == 5);
            OurType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
            s.get(4, x);
            assert(x == ARRAY[2]);
            for (size_t k = 1; k < 4; k++)
            {
                x = SOMEVAL;
                s.get(k, x);
                assert(x == ARRAY[1]);
            }
        } break; case 45: {
            assert(! s.insert(1, SOMEVAL)  &&  s.size() == 0);
        } break; case 46: {
            assert(! s.insert(-1, SOMEVAL)  &&  s.size() == 0);
        } break; case 47: {
            s.insert(0, SOMEVAL);
            assert(! s.insert(2, SOMEVAL)  &&  s.size() == 1);
        } break; case 48: {
            s.insert(0, SOMEVAL);
            assert(! s.erase(1)  &&  s.size() == 1);
        } break; case 49: {
            s.insert(0, SOMEVAL);
            assert(s.erase(0)  &&  s.size() == 0);
        } break; case 50: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            assert(s.erase(4)  &&  s.size() == 4);
        } break; case 51: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            s.erase(4);
            OurType x;
            s.get(3, x);
            assert(x == ARRAY[3]);
        } break; case 52: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            assert(s.erase(1)  &&  s.size() == 4);
        } break; case 53: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            s.erase(1);
            OurType x;
            s.get(0, x);
            assert(x == ARRAY[0]);
            for (size_t k = 1; k < 4; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[k+1]);
            }
        } break; case 54: {
            s.insert(0,SOMEVAL);
            assert(s.remove(SOMEVAL) == 1);
        } break; case 55: {
            s.insert(0,SOMEVAL);
            s.remove(SOMEVAL);
            assert(s.size() == 0);
        } break; case 56: {
            s.insert(0, ARRAY[0]);
            assert(s.remove(ARRAY[1]) == 0);
        } break; case 57: {
            s.insert(0, ARRAY[0]);
            s.remove(ARRAY[1]);
            assert(s.size() == 1);
        } break; case 58: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[1]);
            s.insert(4, ARRAY[0]);
            s.remove(ARRAY[2]);
            OurType x;
            for (size_t k = 0; k < 2; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[5-1-k]);
            }
            for (size_t k = 2; k < 4; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[5-2-k]);
            }
        } break; case 59: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            s.insert(5, ARRAY[2]);
            assert(s.remove(ARRAY[2]) == 4);
        } break; case 60: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            s.insert(5, ARRAY[2]);
            s.remove(ARRAY[2]);
            assert(s.size() == 2);
        } break; case 61: {
            s.insert(0, ARRAY[4]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            s.insert(4, ARRAY[2]);
            s.insert(5, ARRAY[2]);
            s.remove(ARRAY[2]);
            OurType x;
            for (size_t k = 0; k < 2; k++)
            {
                x = ARRAY[0];
                s.get(k, x);
                assert(x == ARRAY[4]);
            }
        } break; case 62: {
            s.insert(0, ARRAY[2]);
            s.insert(1, ARRAY[2]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[2]);
            s.insert(4, ARRAY[2]);
            s.remove(ARRAY[2]);
            assert(s.size() == 0);
        } break; case 63: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            OurType x;
            assert(! s.get(-1, x));
        } break; case 64: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            OurType x = ARRAY[1];
            s.get(-1, x);
            assert(x == ARRAY[1]);
        } break; case 65: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            OurType x;
            assert(! s.get(3, x));
        } break; case 66: {
            s.insert(0, SOMEVAL);
            s.insert(1, SOMEVAL);
            s.insert(2, SOMEVAL);
            OurType x = ARRAY[1];
            s.get(3, x);
            assert(x == ARRAY[1]);
        } break; case 67: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            assert(! s.set(-1, ARRAY[3]));
        } break; case 68: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.set(-1, ARRAY[3]);
            assert(s.size() == 3);
            for (size_t k = 0; k < 3; k++)
            {
                OurType x = SOMEVAL;
                assert(s.get(k,x)  &&  x == ARRAY[k]);
            }
        } break; case 69: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            assert(! s.set(3, ARRAY[3]));
        } break; case 70: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.set(-1, ARRAY[3]);
            assert(s.size() == 3);
            for (size_t k = 0; k < 3; k++)
            {
                OurType x = SOMEVAL;
                assert(s.get(k,x)  &&  x == ARRAY[k]);
            }
        } break; case 71: {
            s.insert(SOMEVAL);
            assert(s.find(DEFAULT) == -1);
        } break; case 72: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            assert(s.find(ARRAY[4]) == 1);
        } break; case 73: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[4]);
            assert(s.find(ARRAY[3]) == -1);
        } break; case 74: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2;
                s2.insert(0, ARRAY[3]);
                s2.insert(1, ARRAY[4]);
                s.swap(s2);
                assert(s.size() == 2  &&  s2.size() == 3);
            }
        } break; case 75: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2;
                s2.insert(0, ARRAY[3]);
                s2.insert(1, ARRAY[4]);
                s.swap(s2);
                OurType x;
                assert(s.get(0, x)  &&  x == ARRAY[3]);
                assert(s.get(1, x)  &&  x == ARRAY[4]);
                assert(s2.get(0, x)  &&  x == ARRAY[0]);
                assert(s2.get(1, x)  &&  x == ARRAY[1]);
                assert(s2.get(2, x)  &&  x == ARRAY[2]);
            }
        } break; case 76: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            s.insert(3, ARRAY[3]);
            s.insert(4, ARRAY[4]);
            {
                Sequence s2;
                s2.insert(0, ARRAY[3]);
                s2.insert(1, ARRAY[4]);
                s2.insert(2, ARRAY[0]);
                int n = nasstcopys();
                s.swap(s2);
                int n2 = nasstcopys();
                assert(n2 >= n  &&  n2 <= n+3);  // swapping head nodes OK
            }
        } break; case 77: {
            const size_t BIG = 600;
            for (size_t k = 0; k < BIG; k++)
                assert(s.insert(SOMEVAL) != -1);
            assert(s.size() == BIG);
            for (size_t k = 0; k < BIG; k++)
            {
                OurType x = DEFAULT;
                s.get(k, x);
                assert(x == SOMEVAL);
            }
        } break; case 78: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0,SOMEVAL);
                assert(itemcount() > before);
            }
            assert(itemcount() == before);
        } break; case 79: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(0, ARRAY[2]);
                s2.insert(2, ARRAY[3]);
                s2.insert(1, ARRAY[2]);
                s2.erase(0);
                s2.remove(ARRAY[2]);
                s2.insert(0, ARRAY[4]);
                s2.insert(s2.size(), ARRAY[4]);
                s2.remove(ARRAY[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 80: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(0, ARRAY[2]);
                s2.insert(2, ARRAY[3]);
                s2.insert(1, ARRAY[2]);
                Sequence s3(s2);
                s3.insert(0, ARRAY[1]);
                s3.insert(0, ARRAY[2]);
                s3.insert(2, ARRAY[3]);
                s3.insert(1, ARRAY[2]);
                s3.erase(0);
                s3.remove(ARRAY[2]);
                s3.insert(0, ARRAY[4]);
                s3.insert(s3.size(), ARRAY[4]);
                s3.remove(ARRAY[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 81: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                int mid = itemcount();
                Sequence s3(s2);
                assert(s3.size() == 3);
                assert(itemcount() - mid == mid - before);
            }
            assert(itemcount() == before);
        } break; case 82: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2(s);
                s2.insert(3, ARRAY[3]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 83: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2(s);
                s2.insert(0, ARRAY[3]);
                OurType x;
                assert(s2.get(0, x)  &&  x == ARRAY[3]);
                assert(s2.get(1, x)  &&  x == ARRAY[0]);
                assert(s2.get(2, x)  &&  x == ARRAY[1]);
                assert(s2.get(3, x)  &&  x == ARRAY[2]);
            }
        } break; case 84: {
            s.insert(0, ARRAY[0]);
            s.insert(1, ARRAY[1]);
            s.insert(2, ARRAY[2]);
            {
                Sequence s2(s);
                s2.insert(0, ARRAY[3]);
                OurType x;
                assert(s.get(0, x)  &&  x == ARRAY[0]);
                assert(s.get(1, x)  &&  x == ARRAY[1]);
                assert(s.get(2, x)  &&  x == ARRAY[2]);
            }
        } break; case 85: {
            {
                Sequence s2;
                Sequence s3(s2);
                s2.insert(0, ARRAY[0]);
                s3.insert(0, ARRAY[1]);
                assert(s2.size() == 1  &&  s3.size() == 1);
                OurType x;
                s2.get(0, x);
                assert(x == ARRAY[0]);
                s3.get(0, x);
                assert(x == ARRAY[1]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 86: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(0, ARRAY[2]);
                s2.insert(2, ARRAY[3]);
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s3 = s2;
                s3.insert(1, ARRAY[2]);
                s3.erase(0);
                s3.remove(ARRAY[2]);
                s3.insert(0, ARRAY[4]);
                s3.insert(s3.size(), ARRAY[4]);
                s3.remove(ARRAY[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 87: {
            int before = itemcount();
            {
                Sequence s2;
                Sequence s3;
                int mid = itemcount();
                s2.insert(0, ARRAY[0]);
                s2.insert(1, ARRAY[1]);
                assert(s2.size() == 2);
                s2 = s3;
                assert(itemcount() == mid);
                s2.insert(0, ARRAY[2]);
                s3.insert(0, ARRAY[3]);
                assert(s2.size() == 1  &&  s3.size() == 1);
                OurType x;
                s2.get(0, x);
                assert(x == ARRAY[2]);
                s3.get(0, x);
                assert(x == ARRAY[3]);
            }
            assert(itemcount() == before);
        } break; case 88: {
            int before = itemcount();
            {
                Sequence s2;
                Sequence s3;
                s2.insert(0, ARRAY[0]);
                s2.insert(1, ARRAY[1]);
                s3 = s2;
                s2.insert(2, ARRAY[2]);
                s3.insert(2, ARRAY[3]);
                assert(s2.size() == 3  &&  s3.size() == 3);
                OurType x;
                for (size_t k = 0; k < 2; k++)
                {
                    s2.get(k, x);
                    assert(x == ARRAY[k]);
                    s3.get(k, x);
                    assert(x == ARRAY[k]);
                }
                s2.get(2, x);
                assert(x == ARRAY[2]);
                s3.get(2, x);
                assert(x == ARRAY[3]);
            }
            assert(itemcount() == before);
        } break; case 89: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                int mid = itemcount();
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s3 = s2;
                assert(itemcount() - mid == mid - before);
            }
        } break; case 90: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s3 = s2;
                s3.insert(3, ARRAY[3]);
                assert(s3.size() == s2.size()+1);
                for (int k = 0; k < s2.size(); k++)
                {
                    OurType x2 = SOMEVAL;
                    OurType x3 = DEFAULT;
                    s2.get(k,x2);
                    s3.get(k,x3);
                    assert(x2 == x3);
                }
            }
        } break; case 91: {
            int before = itemcount();
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                Sequence s3;
                s3.insert(0, ARRAY[5]);
                s3.insert(0, ARRAY[4]);
                s2 = s3;
                assert(s2.size() == s3.size());
                OurType x;
                assert(!s2.get(2, x));
                s2.insert(0, ARRAY[3]);
                assert(s2.size() == s3.size()+1);
                assert(s2.get(0, x)  &&  x == ARRAY[3]);
                assert(s2.get(1, x)  &&  x == ARRAY[4]);
                assert(s2.get(2, x)  &&  x == ARRAY[5]);
            }
            assert(itemcount() == before);
        } break; case 92: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                int n2 = itemcount();
                s2 = s2;
                assert(itemcount() == n2);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 93: {
            {
                Sequence s2;
                s2.insert(0, ARRAY[1]);
                s2.insert(1, ARRAY[3]);
                s2.insert(2, ARRAY[2]);
                s2 = s2;
                s2.insert(3, ARRAY[4]);
                OurType x = SOMEVAL;
                s2.get(0, x); assert(x == ARRAY[1]);
                s2.get(1, x); assert(x == ARRAY[3]);
                s2.get(2, x); assert(x == ARRAY[2]);
                s2.get(3, x); assert(x == ARRAY[4]);
            }
        } break; case 94: {
            Sequence s2;
            assert(subsequence(s2,s) == -1);
        } break; case 95: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            Sequence s2;
            assert(subsequence(s2,s) == -1);
        } break; case 96: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            Sequence s2;
            assert(subsequence(s,s2) == -1);
        } break; case 97: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[2]);
            assert(subsequence(s,s) == 0);
        } break; case 98: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[0]);
            assert(subsequence(s,s2) == 2);
        } break; case 99: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[0]);
            s2.insert(1, ARRAY[3]);
            assert(subsequence(s,s2) == -1);
        } break; case 100: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[2]);
            assert(subsequence(s,s2) == -1);
        } break; case 101: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[3]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[0]);
            assert(subsequence(s,s2) == 2);
        } break; case 102: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[0]);
            s2.insert(1, ARRAY[2]);
            assert(subsequence(s,s2) == 3);
        } break; case 103: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[0]);
            s2.insert(1, ARRAY[2]);
            s2.insert(1, ARRAY[3]);
            assert(subsequence(s,s2) == -1);
        } break; case 104: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            Sequence s3;
            interleave(s,s2,s3);
            assert(s3.size() == s.size());
            for (int k = 0; k < s.size(); k++)
            {
                OurType x = SOMEVAL;
                OurType x3 = SOMEVAL;
                s.get(k,x);
                s3.get(k,x3);
                assert(x == x3);
            }
        } break; case 105: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            Sequence s3;
            interleave(s2,s,s3);
            assert(s3.size() == s.size());
            for (int k = 0; k < s.size(); k++)
            {
                OurType x = SOMEVAL;
                OurType x3 = SOMEVAL;
                s.get(k,x);
                s3.get(k,x3);
                assert(x == x3);
            }
        } break; case 106: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            Sequence s3;
            interleave(s,s2,s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                OurType x = SOMEVAL;
                OurType x3 = SOMEVAL;
                if (k % 2 == 0)
                    s.get(k/2,x);
                else
                    s2.get(k/2, x);
                s3.get(k,x3);
                assert(x == x3);
            }
        } break; case 107: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            s.insert(3, ARRAY[0]);
            s.insert(4, ARRAY[2]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            Sequence s3;
            interleave(s,s2,s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                OurType x = SOMEVAL;
                OurType x3 = SOMEVAL;
                if (k >= 2 * s2.size())
                    s.get(k-s2.size(),x);
                else if (k % 2 == 0)
                    s.get(k/2,x);
                else
                    s2.get(k/2, x);
                s3.get(k,x3);
                assert(x == x3);
            }
        } break; case 108: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            s2.insert(3, ARRAY[1]);
            s2.insert(4, ARRAY[3]);
            Sequence s3;
            interleave(s,s2,s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                OurType x = SOMEVAL;
                OurType x3 = SOMEVAL;
                if (k >= 2 * s.size())
                    s2.get(k-s.size(),x);
                else if (k % 2 == 0)
                    s.get(k/2,x);
                else
                    s2.get(k/2, x);
                s3.get(k,x3);
                assert(x == x3);
            }
        } break; case 109: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            s.insert(2, ARRAY[3]);
            Sequence s2;
            s2.insert(0, ARRAY[2]);
            s2.insert(1, ARRAY[0]);
            s2.insert(2, ARRAY[4]);
            Sequence s3;
            s3.insert(0, ARRAY[3]);
            s3.insert(1, ARRAY[2]);
            s3.insert(2, ARRAY[1]);
            interleave(s,s2,s3);
            assert(s3.size() == s.size() + s2.size());
            for (int k = 0; k < s3.size(); k++)
            {
                OurType x = SOMEVAL;
                OurType x3 = SOMEVAL;
                if (k % 2 == 0)
                    s.get(k/2,x);
                else
                    s2.get(k/2, x);
                s3.get(k,x3);
                assert(x == x3);
            }
        } break; case 110: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[2]);
            s2.insert(2, ARRAY[0]);
            interleave(s,s2,s);
            assert(s.size() == 5);
            OurType x = SOMEVAL;
            s.get(0,x); assert(x == ARRAY[1]);
            s.get(1,x); assert(x == ARRAY[3]);
            s.get(2,x); assert(x == ARRAY[4]);
            s.get(3,x); assert(x == ARRAY[2]);
            s.get(4,x); assert(x == ARRAY[0]);
            s2.get(0,x); assert(x == ARRAY[3]);
            s2.get(1,x); assert(x == ARRAY[2]);
            s2.get(2,x); assert(x == ARRAY[0]);
        } break; case 111: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            Sequence s2;
            s2.insert(0, ARRAY[3]);
            s2.insert(1, ARRAY[2]);
            s2.insert(2, ARRAY[0]);
            interleave(s,s2,s2);
            assert(s2.size() == 5);
            OurType x = SOMEVAL;
            s2.get(0,x); assert(x == ARRAY[1]);
            s2.get(1,x); assert(x == ARRAY[3]);
            s2.get(2,x); assert(x == ARRAY[4]);
            s2.get(3,x); assert(x == ARRAY[2]);
            s2.get(4,x); assert(x == ARRAY[0]);
            s.get(0,x); assert(x == ARRAY[1]);
            s.get(1,x); assert(x == ARRAY[4]);
        } break; case 112: {
            s.insert(0, ARRAY[1]);
            s.insert(1, ARRAY[4]);
            interleave(s,s,s);
            assert(s.size() == 4);
            OurType x = SOMEVAL;
            s.get(0,x); assert(x == ARRAY[1]);
            s.get(1,x); assert(x == ARRAY[1]);
            s.get(2,x); assert(x == ARRAY[4]);
            s.get(3,x); assert(x == ARRAY[4]);
        }
    }
}

int main()
{
//    cout << "Enter test number: ";
//    int n;
//    cin >> n;
//    if (n < 1  ||  n > 112)
//    {
//        cout << "Bad test number" << endl;
//        return 1;
//    }
    for (int i = 1; i <= 112; i++)
    {
        testone(i);
        cout << i << endl;
    }
    cout << "Passed" << endl;
}
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
//    t1.swap(t2);
//    assert(t1.size() == 8);
//    assert(t2.get(3,a) == true && a == "mushroom");
//    assert(t2.get(6,a) == false);
//    assert(t1.remove("now") == 8);
//}
