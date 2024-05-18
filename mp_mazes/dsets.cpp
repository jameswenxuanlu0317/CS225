/* Your code here! */
#include "dsets.h"
#include<iostream>
#include<cmath>
void DisjointSets::addelements(int num)
{
    for(int i=0; i<num; i++)
    {
        elements.push_back(-1);
    }
}

int DisjointSets::find(int elem)
{
    if(elements[elem]<0)
    {
        return elem;
    }
    int index=find(elements[elem]);
    elements[elem]=index;
    return index;
}

void DisjointSets::setunion(int a, int b)
{
    int first=find(a);
    int second=find(b);
    if(first==second)
    {
        return;
    }
    if(size(first)>size(second))
    {
        elements[first]+=elements[second];
        elements[second]=first;
    }
    else
    {
        elements[second]+=elements[first];
        elements[first]=second;
    }
}

int DisjointSets::size(int elem)
{
    if(elem<0)
    {
        return -1;
    }
    if(elem>=(int)elements.size())
    {
        return -1;
    }
    return std::abs(elements[find(elem)]);
}