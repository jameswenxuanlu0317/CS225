#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() 
  :traversal(nullptr), pic(nullptr)
{
  /** @todo [Part 1] */

}

ImageTraversal::Iterator::Iterator(const Point startPt, const PNG *pic, double tolerance, ImageTraversal *traversal) 
  :pos(startPt), traversal(traversal), pic(pic), tolerance(tolerance)
{
  current=pic->getPixel(startPt.x, startPt.y);
  traversed.resize(pic->height(), std::vector<bool>());
  for(unsigned int i=0; i<pic->height(); i++)
  {
    traversed[i].resize(pic->width(), false);
  }
  traversed[pos.y][pos.x]=true; 
}

bool ImageTraversal::Iterator::isValid(unsigned int x, unsigned int y)
{
  if(x>=pic->width()||y>=pic->height())
  {
    return false;
  }
  if(x<0||y<0)
  {
    return false; 
  }
  if(calculateDelta(current, pic->getPixel(x,y))>=tolerance)
  {
    return false;
  }
  return true; 
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() 
{
  /** @todo [Part 1] */
  int xval=this->pos.x;
  int yval=this->pos.y;
  traversed[yval][xval]=true;
  if(isValid(xval+1, yval))
  {
    Point pt=Point(xval+1, yval);
    traversal->add(pt);
  }
  if(isValid(xval, yval+1))
  {
    Point pt=Point(xval, yval+1);
    traversal->add(pt);
  }
  
  if(isValid(xval-1, yval))
  {
    Point pt=Point(xval-1, yval);
    traversal->add(pt);
  }
  if(isValid(xval, yval-1))
  {
    Point pt=Point(xval, yval-1);
    traversal->add(pt);
  }
  Point pt=traversal->pop();
  while(!traversal->empty()&&traversed[pt.y][pt.x])
  {
    pt=traversal->pop();
  }
  if(!traversed[pt.y][pt.x])
  {
    pos=pt;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->pos;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool emptyThis=false;
  bool emptyOther=false; 
  if(traversal==NULL)
  {
    emptyThis=true;
  }
  if(other.traversal==NULL)
  {
    emptyOther=true;
  }
  if(!emptyThis)
  {
    emptyThis=traversal->empty();
  }
  if(!emptyOther)
  {
    emptyOther=other.traversal->empty();
  }
  if(emptyThis&&emptyOther)
  {
    return false;
  }
  if(!emptyThis&&!emptyOther)
  {
    return traversal!=other.traversal;
  }

  return true;
}

