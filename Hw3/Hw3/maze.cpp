//
//  maze.cpp
//  Hw3
//
//  Created by Mint MSH on 2/9/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    if (sr == er && sc == ec)
        return true;
    
    if (maze[sr][sc] != '.')
        return false;
    
    int next[4][2]= {{-1,0},{0,1},{1,0},{0,-1}}; // north, east, south, west
    
    maze[sr][sc] = 'S';
    for (int i = 0; i <= 3; i++)
    {
        int curR = sr + next[i][0];
        int curC = sc + next[i][1];
        if (maze[curR][curC] == '.')
        {
            if (pathExists(maze, nRows, nCols, curR, curC, er, ec) == true)
                return true;
        }
    }
    return false;
}

//int main()
//{
//    string maze1[10] = {
//        "XXXXXXXXXX'",
//        "X.X..X...X'",
//        "X.XX.X.XXX'",
//        "X....X.X.X'",
//        "XX.X.X...X'",
//        "XXX..X.X.X'",
//        "X...X...XX'",
//        "X.XX..X.XX'",
//        "X....X...X'",
//        "XXXXXXXXXX'",
//    };
//    
//    string maze2[10] = {
//        "XXXXXXXXXX'",
//        "X.X..X...X'",
//        "XXXX.X.XXX'",
//        "X....X.X.X'",
//        "XX.X.X...X'",
//        "XXX..X.X.X'",
//        "X...X...XX'",
//        "X.XX..X.XX'",
//        "X....X...X'",
//        "XXXXXXXXXX'",
//    };
//    
//    string maze3[10] = {
//        "XXXXXXXXXX'",
//        "XX.....XXX'",
//        "X..XX....X'",
//        "X...X...XX'",
//        "X.X.XXX..X'",
//        "XXXX..X..X'",
//        "XX....X..X'",
//        "X.......XX'",
//        "X..XXXXXXX'",
//        "XXXXXXXXXX'",
//    };
//    
//    string maze4[10] = {
//        "XXXXXXXXXX'",
//        "XX.....XXX'",
//        "X..XX....X'",
//        "X...X...XX'",
//        "X.X.XXX..X'",
//        "XXXX..X..X'",
//        "XX....X..X'",
//        "X.X.....XX'",
//        "X..XXXXXXX'",
//        "XXXXXXXXXX'",
//    };
//    
//    assert(pathExists(maze1, 10, 10, 6, 2, 1, 1));
//    assert(!pathExists(maze2, 10, 0, 8, 6, 1, 1));
//    assert(pathExists(maze3, 10, 10, 6, 2, 7, 1));
//    assert(!pathExists(maze4, 10, 10, 5, 4, 7, 1));
//    
//    cout << "lalala" << endl;
//
//}
