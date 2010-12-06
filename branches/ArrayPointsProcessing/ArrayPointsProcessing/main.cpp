#include <fstream>
#include "PointArrayStructure.h"

using namespace std;

void LoadArray(PointArray& pointArray, const char* nameFile)
{
    std::ifstream fs(nameFile,std::ios::in | std::ios::binary);

    fs.read((char*)&pointArray.sizeX,sizeof(int));
    fs.read((char*)&pointArray.sizeY,sizeof(int));
    fs.read((char*)&pointArray.sizeZ,sizeof(int));

    fs.read((char*)&pointArray.scaleX,sizeof(float));
    fs.read((char*)&pointArray.scaleX,sizeof(float));
    fs.read((char*)&pointArray.scaleX,sizeof(float));

    pointArray.dataX = new short[pointArray.sizeX];
    pointArray.dataY = new short[pointArray.sizeY];
    pointArray.dataZ = new short[pointArray.sizeZ];

    fs.read((char*)pointArray.dataX,2*pointArray.sizeX);
    fs.read((char*)pointArray.dataY,2*pointArray.sizeY);
    fs.read((char*)pointArray.dataZ,2*pointArray.sizeZ);

    fs.close();
}

void DestroyArray(PointArray& pointArray)
{
    delete [] pointArray.dataX;
    delete [] pointArray.dataY;
    delete [] pointArray.dataZ;
}


int main(int argc, char *argv[])
{
    PointArray pointArray;
    LoadArray(pointArray, "brain_t1.bin");
    DestroyArray(pointArray);
}