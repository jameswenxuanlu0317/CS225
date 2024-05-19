#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include "Image.h"
using cs225::HSLAPixel;

void Image::lighten()
{
    unsigned x, y;
    for(x=0; x<width();x++)
    {
        for(y=0; y<height(); y++)
        {
            if(getPixel(x,y).l<=0.9)
            {
                getPixel(x,y).l=getPixel(x,y).l+0.1;
            }
            else
            {
                getPixel(x,y).l=1;
            }
        }
    }
}
void Image::lighten(double amount)
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).l<=1.0-amount)
            {
                this->getPixel(x,y).l=this->getPixel(x,y).l+amount;
            }
            else
            {
                this->getPixel(x,y).l=1;
            }
        }
    }
}
void Image::darken()
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).l>=0.1)
            {
                this->getPixel(x,y).l=this->getPixel(x,y).l-0.1;
            }
            else
            {
                this->getPixel(x,y).l=0;
            }
        }
    }
}
void Image::darken(double amount)
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).l>=amount)
            {
                this->getPixel(x,y).l=this->getPixel(x,y).l-amount;
            }
            else
            {
                this->getPixel(x,y).l=0;
            }
        }
    }
}
void Image::saturate()
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).s<=0.9)
            {
                this->getPixel(x,y).s=this->getPixel(x,y).s+0.1;
            }
            else
            {
                this->getPixel(x,y).s=1;
            }
        }
    }
}
void Image::saturate(double amount)
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).s<=1-amount)
            {
                this->getPixel(x,y).s=this->getPixel(x,y).s+amount;
            }
            else
            {
                this->getPixel(x,y).s=1;
            }
        }
    }
}
void Image::desaturate()
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).s>=0.1)
            {
                this->getPixel(x,y).s=this->getPixel(x,y).s-0.1;
            }
            else
            {
                this->getPixel(x,y).s=0;
            }
        }
    }
}
void Image::desaturate(double amount)
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            if(this->getPixel(x,y).s>=amount)
            {
                this->getPixel(x,y).s=this->getPixel(x,y).s-amount;
            }
            else
            {
                this->getPixel(x,y).s=0;
            }
        }
    }
}
void Image::grayscale()
{
    for(unsigned int x=0; x<this->width();x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            this->getPixel(x,y).s=0;
        }
    }
}
void Image::rotateColor(double degrees)
{
    for(unsigned int x=0; x<this->width(); x++)
    {
        for(unsigned int y=0; y<this->height(); y++)
        {
            HSLAPixel &pixel=this->getPixel(x,y);
            pixel.h+=degrees;
            if(pixel.h>360)
            {
                pixel.h-=360;
            }
            else if(pixel.h+degrees<0)
            {
                pixel.h+=360;
            }
        }
    }
}
void Image::illinify()
{
    for (unsigned x = 0; x < this->width(); x++) 
    {
        for (unsigned y = 0; y < this->height(); y++) 
        {
            if ((this->getPixel(x, y).h>114) && (this->getPixel(x, y).h < 294)) 
            {
                this->getPixel(x, y).h = 216;
            }
            else 
            {
                this->getPixel(x, y).h = 11;
            }
        }
    }
}
void Image::scale(double factor)
{
    unsigned int newWidth=this->width()*factor;
    unsigned int newHeight=this->height()*factor;
    Image *newImage=new Image;
    *newImage=*this;
    this->resize(newWidth, newHeight);
    for(unsigned x=0; x<this->width();x++)
    {
        for(unsigned y=0; y<this->height(); y++)
        {
            unsigned w=x/factor;
            unsigned h=y/factor;
            cs225::HSLAPixel & newPixel = this->getPixel(x, y);
            cs225::HSLAPixel & oldPixel = newImage->getPixel(w, h);
            newPixel = oldPixel;
        }
    }
}
void Image::scale(unsigned w, unsigned h)
{
    unsigned x=w/this->width();
    unsigned y=h/this->height();
    if(x>y)
    {
        scale(y);
    }
    else{
        scale(x);
    }
}