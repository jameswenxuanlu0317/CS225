/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* ans=new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> points;
    map<Point<3>, TileImage*> map;
    for(vector<TileImage>::iterator i=theTiles.begin(); i!=theTiles.end(); i++)
    {
        LUVAPixel pixel=i->getAverageColor();
        Point<3> pt=convertToXYZ(pixel);
        points.push_back(pt);
        map[pt]=&*i;
    }
    KDTree<3> tree(points);
    for(int x=0; x<ans->getRows();x++)
    {
        for(int y=0; y<ans->getColumns();y++)
        {
            LUVAPixel pixel=theSource.getRegionColor(x,y);
            Point<3> convert=convertToXYZ(pixel);
            Point<3> closest=tree.findNearestNeighbor(convert);
            TileImage* closest_tile=map[closest];
            ans->setTile(x, y, closest_tile);
        }
    }

    return ans;
}

