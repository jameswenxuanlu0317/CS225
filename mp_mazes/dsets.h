/* Your code here! */
#pragma once
#include <stdlib.h>
#include <vector>
class DisjointSets
{
    public:
        //DisjointSets();
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
    private:
        std::vector<int> elements;
};