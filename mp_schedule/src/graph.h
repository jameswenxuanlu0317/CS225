#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "schedule.h"
#include "edge.h"
using namespace std;
class graph
{
    public:
        graph();
        graph(V2D courses);
        ~graph();

    private:
        void buildGraph(V2D courses);
        void buildGraphHelper();
        bool graphColoring();
        vector<vector<int>> adjacency_matrix;
       
};