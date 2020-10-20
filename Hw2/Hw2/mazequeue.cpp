////
////  mazequeue.cpp
////  Hw2
////
////  Created by Mint MSH on 2/5/17.
////  Copyright © 2017 Mint MSH. All rights reserved.
////
//
//#include <stdio.h>
//#include <string>
//#include <queue>
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
//    queue<Coord> coordQueue;     // declare a stack of Coords
//    coordQueue.push(Coord(sr,sc));
//    maze[sr][sc] = 's';
//    Coord cur(0,0);
//    
//    while (!coordQueue.empty())
//    {
//        cur = coordQueue.front();
//        coordQueue.pop();
//        if (cur.r() == er && cur.c() == ec)
//            return true;
//        
//        if (maze[cur.r()-1][cur.c()] == '.')
//        {
//            coordQueue.push(Coord(cur.r()-1,cur.c()));
//            maze[cur.r()-1][cur.c()] = 's';
//        }
//        if (maze[cur.r()][cur.c()+1] == '.')
//        {
//            coordQueue.push(Coord(cur.r(),cur.c()+1));
//            maze[cur.r()][cur.c()+1] = 's';
//        }
//        if (maze[cur.r()+1][cur.c()] == '.')
//        {
//            coordQueue.push(Coord(cur.r()+1,cur.c()));
//            maze[cur.r()+1][cur.c()] = 's';
//        }
//        if (maze[cur.r()][cur.c()-1] == '.')
//        {
//            coordQueue.push(Coord(cur.r(),cur.c()-1));
//            maze[cur.r()][cur.c()-1] = 's';
//        }
//    }
//    return false;
//}
