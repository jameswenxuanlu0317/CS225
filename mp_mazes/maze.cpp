/* Your code here! */
#include "maze.h"
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <cstdlib>
using namespace std;
using namespace cs225;

SquareMaze::SquareMaze()
{
    width_=0;
    height_=0;
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if(dir==0)
    {
        if(x>=width_-1)
        {
            return false;
        }
        else 
        {
            return !walls[x+y*width_].first;
        }
    }
    else if(dir==1)
    {
        if(y>=height_-1)
        {
            return false;
        }
        else
        {
            return !walls[x+y*width_].second;
        }
        
    }
    else if(dir==2)
    {
        if(x<1)
        {
            return false;
        }
        else
        {
            return !walls[x-1+y*width_].first;
        }
    }
    else if(dir==3)
    {
        if(y<1)
        {
            return false;
        }
        else
        {
            return !walls[x+(y-1)*width_].second;
        }
    }
    else
    {
      return false;
    }
}

PNG* SquareMaze::drawMaze() const
{
  int x=width_*10+1;
  int y=height_*10+1;
  PNG* png = new PNG(x, y);
  for(int i=0; i<width_; i++)
  {
    for(int j=0; j<height_; j++)
    {
      if(j==0)
      {
        for(unsigned x=0; x<10; x++)
        {
          unsigned a=i*10+x;
          if(a<1||a>9)
          {
            HSLAPixel & pix=png->getPixel(a, 0);
            pix.l=0;
          }
        }
      }
      if(i==0)
      {
        for(unsigned x=0; x<10; x++)
        {
          unsigned a=j*10+x;
          HSLAPixel & pix=png->getPixel(0,a);
          pix.l=0;
        }
      }
      if(!canTravel(i, j, 0))
      {
        for(unsigned x=0; x<=10; x++)
        {
          unsigned a=(i+1)*10;
          unsigned b=j*10+x;
          HSLAPixel & pix=png->getPixel(a, b);
          pix.l=0;
        }
      }
      if(!canTravel(i, j, 1))
      {
        for(unsigned x=0; x<=10; x++)
        {
          unsigned a=i*10+x;
          unsigned b=(j+1)*10;
          HSLAPixel & pix=png->getPixel(a, b);
          pix.l=0;
        }
      }
    }
  }
  return png;
}
PNG *SquareMaze::drawMazeWithSolution()
{
    PNG* img=drawMaze();
    std::vector<int> path=solveMaze();
    int x,y;
    x=5;
    y=5;
    for(unsigned i=0; i<path.size(); i++)
    {
        if(path[i]==0)
        {
            for(int j=0; j<10; j++)
            {
                HSLAPixel &pixel=img->getPixel(x,y);
                pixel.s=1;
                pixel.l=0.5;
                pixel.h=0;
                x++;
            }
        }
        else if(path[i]==1)
        {
            for(int j=0; j<10; j++)
            {
                HSLAPixel &pixel=img->getPixel(x,y);
                pixel.s=1;
                pixel.l=0.5;
                pixel.h=0;
                y++;
            }
        }
        else if(path[i]==2)
        {
            for(int j=0; j<10; j++)
            {
                HSLAPixel &pixel=img->getPixel(x,y);
                pixel.s=1;
                pixel.l=0.5;
                pixel.h=0;
                x--;
            }
        }
        else if(path[i]==3)
        {
            for(int j=0; j<10; j++)
            {
                HSLAPixel &pixel=img->getPixel(x,y);
                pixel.s=1;
                pixel.l=0.5;
                pixel.h=0;
                y--;
            }
        }
    }
    HSLAPixel &pix=img->getPixel(x,y);
    pix.l=0.5;
    pix.h=0;
    pix.s=1;
    pix.a=1;
    x=x-4;
    y=y+5;
    for(int j=0; j<9; j++)
    {
        HSLAPixel &pixel=img->getPixel(x,y);
        pixel.a=1;
        pixel.l=1;
        x++;
    }
    return img;
}
void SquareMaze::makeMaze(int width, int height)
{
  width_ = width;
  height_ = height;
  int size = width_*height_;
  sets.addelements(size);
  for(int i = 0; i<size; i++) 
  {
    walls.push_back(pair<bool, bool> (true, true)); 
  }
  int j = 0;
  while(j<size-1) 
  {
    int x_val = rand() %width_;
    int y_val = rand() %height_;
    bool random = rand() % 2;
    if(random) 
    {

      if(walls[x_val+y_val*width_].first)
      {
        if(x_val<width_-1)
        {
          if(sets.find(x_val+y_val*width_)!=sets.find(x_val+y_val*width_+1))
          {
            walls[x_val + y_val*width_].first = false;
            sets.setunion(sets.find(x_val + y_val*width_),sets.find(x_val + y_val*width_+1));
            j++;
          }
        }
      }
    }
    else
    {
      if(walls[x_val+y_val*width_].second)
      {
        if(y_val<height_-1)
        {
          if(sets.find(x_val+y_val*width_)!=sets.find(x_val+(y_val+1)*width_))
          {
            walls[x_val + y_val*width_].second = false;
            sets.setunion(sets.find(x_val + y_val*width_), sets.find(x_val + (y_val+1)*width_));
            j++;
          }
        }
      }
    }
  }
}
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if(dir==0)
    {
        walls[y*width_+x].first=exists;
    }
    else if(dir==1)
    {
        walls[y*width_+x].second=exists;
    }
}
vector<int> SquareMaze::solveMaze()
{
  vector<int> path;
  std::vector<int> down;
  map<int, int> it;
  vector<bool> passed;
  int size=width_*height_;
  for(int i =0; i<size; i++)
  {
    passed.push_back(false);
  }
  queue<int> traversal;
  traversal.push(0);
  passed[0] = true;

  while(!traversal.empty()) 
  {
    int temp = traversal.front();
    traversal.pop();
    int x = temp%width_;
    int y = temp/width_;
    if(y == height_-1)
    {
      down.push_back(temp);
    } 
    if(canTravel(x,y,0))
    {
      if(passed[temp+1]==false)
      {
        it.insert(pair<int, int>(temp+1, temp));
        passed[temp+1]=true;
        traversal.push(temp+1);
      }
    }
    if(canTravel(x,y,1))
    {
      if(passed[temp+width_]==false)
      {
        it.insert(pair<int, int>(temp+width_, temp));
        passed[temp+width_]=true;
        traversal.push(temp+width_);
      }
    }
    if(canTravel(x,y,2))
    {
      if(passed[temp-1]==false)
      {
        it.insert(pair<int, int>(temp-1, temp));
        passed[temp-1]=true;
        traversal.push(temp-1);
      }
    }
    if(canTravel(x,y,3))
    {
      if(passed[temp-width_]==false)
      {
        it.insert(pair<int, int>(temp-width_, temp));
        passed[temp-width_]=true;
        traversal.push(temp-width_);
      }
    }
  }
  stack<int> stk;
  int last = width_-1;
  while(down[last] == down[last-1]) 
  {
    last=-1;
  }
  int start = down[last];
  while(start !=0) 
  {
    int previous = it[start];
    if(start == previous+1)
    {
      stk.push(0);
    } 
    else if(start == previous + width_)
    {
      stk.push(1);
    }
    else if(start == previous-1)
    {
      stk.push(2);
    }
    else if(start==previous-width_)
    {
      stk.push(3);
    }
    start = previous;
  }
  int size_=stk.size();
  for(int i=0; i<size_; i++ ) 
  {
    path.push_back(stk.top());
    stk.pop();
  }
  return path;
}