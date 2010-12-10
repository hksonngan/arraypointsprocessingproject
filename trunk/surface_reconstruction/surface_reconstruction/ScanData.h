#pragma once

struct Layer {
    short *data;
    size_t sizeX, sizeY;
    float scaleX, scaleY;

    Layer() : data(0), sizeX(0), sizeY(0), scaleX(0), scaleY(0) {};
    Layer(short*_data, size_t _sizeX, size_t _sizeY, float _scaleX, float _scaleY)
        : data(_data), sizeX(_sizeX), sizeY(_sizeY), scaleX(_scaleX), scaleY(_scaleY) {};


};

class ScanData {
public:
    short *data;
    size_t sizeX, sizeY, sizeZ;
    float scaleX, scaleY, scaleZ;

    ScanData();
    ScanData(const char *pathToBinFile);
    ~ScanData();

    void ReleaseResources();

    bool LoadData(const char *pathToBinFile);

    Layer GetLayer(size_t z); // возвращает слой с данными от всего массива, при изменении этого слоя, изменятся и основные данные
    short& GetDensity(size_t x, size_t y, size_t z);
    short& GetDensity(Layer &layer, size_t x, size_t y);
};