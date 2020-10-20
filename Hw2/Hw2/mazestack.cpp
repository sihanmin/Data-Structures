//
//  mazestack.cpp
//  Hw2
//
//  Created by Mint MSH on 2/4/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

//#include <stdio.h>
//#include <string>
//#include <stack>
//using namespace std;
//
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
//// Return true if there is a path from (sr,sc) to (er,ec)
//// through the maze; return false otherwise
//{
//    stack<Coord> coordStack;     // declare a stack of Coords
//    coordStack.push(Coord(sr,sc));
//    maze[sr][sc] = 's';
//    Coord cur(0,0);
//    
//    while (!coordStack.empty())
//    {
//        cur = coordStack.top();
//        coordStack.pop();
//        if (cur.r() == er && cur.c() == ec)
//            return true;
//        
//        if (maze[cur.r()-1][cur.c()] == '.')
//        {
//            coordStack.push(Coord(cur.r()-1,cur.c()));
//            maze[cur.r()-1][cur.c()] = 's';
//        }
//        if (maze[cur.r()][cur.c()+1] == '.')
//        {
//            coordStack.push(Coord(cur.r(),cur.c()+1));
//            maze[cur.r()][cur.c()+1] = 's';
//        }
//        if (maze[cur.r()+1][cur.c()] == '.')
//        {
//            coordStack.push(Coord(cur.r()+1,cur.c()));
//            maze[cur.r()+1][cur.c()] = 's';
//        }
//        if (maze[cur.r()][cur.c()-1] == '.')
//        {
//            coordStack.push(Coord(cur.r(),cur.c()-1));
//            maze[cur.r()][cur.c()-1] = 's';
//        }
//    }
//    return false;
//}
