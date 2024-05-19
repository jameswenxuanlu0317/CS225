#include "StickerSheet.h"
#include "Image.h"
StickerSheet::StickerSheet(const Image&picture, unsigned max)
{
    maximum=max;
    grid=new Image*[max];
    for(unsigned int i=0; i<max;i++)
    {
        grid[i]=nullptr;
    }
    x_val=new unsigned[max];
    y_val=new unsigned[max];
    copy=picture;
}

StickerSheet::~StickerSheet()
{
    deletes();
}

void StickerSheet::deletes()
{
    delete[] grid;
    delete[] x_val;
    delete[] y_val;
}

StickerSheet::StickerSheet (const StickerSheet &other)
{
    getCopy(other);
}

void StickerSheet::getCopy(const StickerSheet &other)
{
    maximum=other.maximum;
    grid=new Image*[maximum];
    copy=other.copy;
    for(unsigned int i=0; i<maximum; i++)
    {
        grid[i]=nullptr;
    }
    x_val=new unsigned[maximum];
    y_val=new unsigned[maximum];
    for(unsigned int x=0; x<maximum; x++)
    {
        grid[x]=other.grid[x];
        x_val[x]=other.x_val[x];
        y_val[x]=other.y_val[x];
    }
}



const StickerSheet&StickerSheet::operator= (const StickerSheet &other)
{
    deletes();
    getCopy(other);
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max)
{
    Image **image=new Image*[max];
    for(unsigned int i=0; i<max;i++)
    {
        image[i]=nullptr;
    }
    unsigned *new_x_val=new unsigned[max];
    unsigned *new_y_val=new unsigned[max];
    if(maximum<max)
    {
        for(unsigned int i=0; i<max; i++)
        {
           if(i<maximum)
           {
            image[i]=grid[i];
            new_x_val[i]=x_val[i];
            new_y_val[i]=y_val[i];
           }
           else
           {
               image[i]=nullptr;
           }
        }
    }
    else if(maximum>max)
    {
        for(unsigned int i=0; i<max; i++)
        {
            image[i]=grid[i];
            new_x_val[i]=x_val[i];
            new_y_val[i]=y_val[i];
        }
    }
    deletes();
    grid=image;
    x_val=new_x_val;
    y_val=new_y_val;
    maximum=max;
}
int StickerSheet::addSticker (Image & sticker, unsigned x, unsigned y)
{
    for(unsigned int i=0; i<maximum; i++)
    {
        if(grid[i]==nullptr)
        {
            grid[i]=&sticker;
            x_val[i]=x;
            y_val[i]=y;
            return i;
        }
    }
    return -1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y)
{
    if(index<0||index>=maximum||grid[index]==nullptr)
    {
        return false;
    }
    else
    {
        x_val[index]=x;
        y_val[index]=y;
        return true;
    }
}
void StickerSheet::removeSticker (unsigned index)
{
    if(index>=0&&index<maximum)
    {
        grid[index]=nullptr;
    }
}
Image * StickerSheet::getSticker (unsigned index)
{
    if(index<0||index>=maximum||grid[index]==nullptr)
    {
        return NULL;
    }
    else
    {
        return grid[index];
    }
}
Image StickerSheet::render () const
{
    unsigned int x=copy.width();
    unsigned int y=copy.height();
    for(unsigned int i=0; i<maximum; i++)
    {
        if(grid[i]==nullptr)
        {

        }
        else
        {
            if(x_val[i]+grid[i]->width()>x)
            {
                x=x_val[i]+grid[i]->width();
            }
            if(y_val[i]+grid[i]->height()>y)
            {
                y=y_val[i]+grid[i]->height();
            }
        }
    }
    Image image=copy;
    image.resize(x,y);
    for(unsigned int i=0; i<maximum; i++)
    {
        if(grid[i]==nullptr)
        {

        }
        else
        {
            for(unsigned int j=0; j<grid[i]->width();j++)
            {
                for(unsigned int k=0; k<grid[i]->height(); k++)
                {
                    cs225::HSLAPixel & image_pixel = image.getPixel(j + x_val[i], k + y_val[i]);
                    cs225::HSLAPixel & sticker_pixel = grid[i]->getPixel(j, k);
                    if(sticker_pixel.a!=0)
                    {
                        image_pixel=sticker_pixel;
                    }
                }
            }   
        }        
    }
    return image;
}
