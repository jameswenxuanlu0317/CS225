#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker(PNG &png_, Point center_, int x);
private:
  PNG png;
  Point center;
  HSLAPixel color1;
  HSLAPixel color2;
  int colorPick;

};
