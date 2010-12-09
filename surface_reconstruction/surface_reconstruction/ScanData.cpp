#include "stdafx.h"

#include "ScanData.h"

#include <fstream>

using namespace std;

ScanData::ScanData() {
    data = 0;
    sizeX = sizeY = sizeZ = 0;
    scaleX = scaleY = scaleZ = 0;
}

ScanData::ScanData(const char *pathToBinFile) {
    LoadData(pathToBinFile);
}

ScanData::~ScanData() {
    ReleaseResources();
}

void ScanData::ReleaseResources() {
    delete[] data;
    data = 0;
    sizeX = sizeY = sizeZ = 0;
    scaleX = scaleY = scaleZ = 0;
}

bool ScanData::LoadData(const char *pathToBinFile) {
    ifstream fs(pathToBinFile, std::ios::in | std::ios::binary);

    if (!fs) {
        return false;
    }

    ReleaseResources();

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

Layer ScanData::GetLayer(size_t z) {
    return Layer(data + sizeX*sizeZ*z, sizeX, sizeY, scaleX, scaleY);
}

short& ScanData::GetDensity(Layer &layer, size_t x, size_t y) {
    return layer.data[x + y * layer.sizeX];
}

short& ScanData::GetDensity(size_t x, size_t y, size_t z) {
    return data[x + y * sizeX + z * sizeX * sizeY];
}