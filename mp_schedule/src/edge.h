#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "schedule.h"
#include "graph.h"
using namespace std;
class edge
{
    public:
        edge(string sources, string target);
        string getSources();
        string getTarget();

    private:
        string source;
        string _target;

};