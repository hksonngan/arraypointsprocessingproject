#ifndef __PointArrayStructure_h__
#define __PointArrayStructure_h__

struct PointArray 
{
    short* dataX;
    short* dataY;
    short* dataZ; 
    int sizeX;
    int sizeY;
    int sizeZ;
    int scaleX;
    int scaleY;
    int scaleZ;
};

#endif