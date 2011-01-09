#include "stdafx.h"
#include "ScanData.h"
#include <fstream>

using namespace std;

short Layer::GetDistination(size_t x1, size_t y1, size_t x2, size_t y2)
{
 return abs(data[x1+y1*sizeX]-data[x2+y2*sizeX]);
}

ScanData::ScanData() 
{
 data = 0;
 sizeX = sizeY = sizeZ = 0;
 scaleX = scaleY = scaleZ = 0;
}

ScanData::ScanData(Layer layer)
{
	sizeX = layer.sizeX;
	sizeY = layer.sizeY;
	sizeZ = 1;
	data = layer.data;
	scaleX = layer.scaleX;
	scaleY = layer.scaleY;
}

ScanData::ScanData(const char *pathToBinFile) { LoadData(pathToBinFile); }

ScanData::~ScanData() { ReleaseResources(); }

void ScanData::ReleaseResources() 
{
 delete [] data;
 data = NULL;
 sizeX = sizeY = sizeZ = 0;
 scaleX = scaleY = scaleZ = 0;
}

bool ScanData::LoadData(const char *pathToBinFile) 
{
 ifstream fs(pathToBinFile, std::ios::in | std::ios::binary);

 if (!fs) return false;
    
 //ReleaseResources();

 fs.read((char*)&sizeX, sizeof(int));
 fs.read((char*)&sizeY, sizeof(int));
 fs.read((char*)&sizeZ, sizeof(int));

 fs.read((char*)&scaleX, sizeof(float));
 fs.read((char*)&scaleY, sizeof(float));
 fs.read((char*)&scaleZ, sizeof(float));

 data = new short[sizeX * sizeY * sizeZ];

 fs.read((char*)data, sizeof(short) * sizeX * sizeY * sizeZ);

 fs.close();

 return true;
}

Layer ScanData::GetLayer(size_t z) { return Layer(data + sizeX*sizeY*z, sizeX, sizeY, scaleX, scaleY); }

short& ScanData::GetDensity(Layer &layer, size_t x, size_t y) { return layer.data[x + y * layer.sizeX]; }

short& ScanData::GetDensity(size_t x, size_t y, size_t z) { return data[x + y * sizeX + z * sizeX * sizeY]; }

double ScanData::GetDistination(size_t x1, size_t y1, size_t z1, 
     							size_t x2, size_t y2, size_t z2) 
{
 return abs(GetDensity(x1, y1, z1)-GetDensity(x2, y2, z2));
}
