#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;
MyColorPicker::MyColorPicker(PNG &png_, Point center_, int x)
{
  png=png_;
  center=center_;
  color1=HSLAPixel(200, 1, 0.5, 1);
  color2=HSLAPixel(100, 1, 0.5, 1);
  colorPick=x;

}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel &pix=png.getPixel(x, y);
  if(colorPick==1)
  {
    pix=color1;
    return pix;
  }
  else
  {
    pix=color2;
    return pix;
  }
}
