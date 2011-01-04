#pragma once
#include "ScanData.h"
#include <list>
#include <iostream>

class GraphVoxel
{
public:

    GraphVoxel();
    GraphVoxel(int maxCountSegments);

protected:
    int maxCountSegments;
    int currentCountSegments;
    int* segments;
};

class Segment;
//описывает воксель
class Voxel
{
public:
    size_t index;
    Voxel* next;
    Segment* segment;

    Voxel();
};

//описывает сегмент в последовательной версии
class Segment
{
public:
    size_t сapacity;//количество тогчек
    Voxel* voxel;//индексы в общем массиве
    short weightSegment;//вес сегмента(максимальный перепад между точками)
    size_t indexSegment;//индекс в сегменте
    Segment* next;

    Segment();
};

class SegmentsTree;

class LayerSegmentsTree
{
public:
    size_t maxCapacity;//максимальное количество точек в сегментах
    Segment* segment;//ссылка на сегменты
    LayerSegmentsTree* up;//вверх дерева
    LayerSegmentsTree* down;//вниз дерева
    size_t segmentCount;//количество сегментов
    Segment* oldSegment;//ссылка на последний сегмент
    SegmentsTree* segmentsTree;//класс хранилище
    Voxel* allVoxel;//указатель на массив вокселей

    LayerSegmentsTree();

    ScanData* CreateData(size_t* index, size_t count);

};

typedef void (funct)(char* str);

//хранилище сегментов разных размеров
class SegmentsTree
{
public:
    size_t countLayer;//количество уровней
    LayerSegmentsTree* root;//корень
    ScanData* scanData; //указатель на исходные данные
    short step;
    int indexSegments;

    //конструктор
    SegmentsTree();
    SegmentsTree(ScanData* data);

    //создать корень
    void CreateRoot(ScanData* data);
    //дать верхний слой
    LayerSegmentsTree* GetOldLayer();
    //определить соседние сегменты
    void DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
        bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w);
    //создать новый слой
    void CreateNewLayer();
};

