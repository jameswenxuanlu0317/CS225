/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
//#include <vector>

class StickerSheet
{
    private:
        Image copy;
        unsigned maximum;
        Image ** grid;
        unsigned *x_val;
        unsigned *y_val;
    public:
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        void deletes();
        void getCopy(const StickerSheet &other);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render () const;
    
    /* data */
    
};



 
