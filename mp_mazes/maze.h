/* Your code here! */
#pragma once
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace std;
using namespace cs225;
class SquareMaze
{
    public:
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        cs225::PNG* drawMaze() const;
        cs225::PNG* drawMazeWithSolution();
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
    private:
        vector<pair<bool, bool>> walls;
        DisjointSets sets;
        int width_;
        int height_;
};