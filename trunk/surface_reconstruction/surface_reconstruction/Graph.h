#pragma once

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
//индексы смещения
const byte relativeIndexMatrix[26][3] = {//i,j,k
    {0,0,0},//0
    {0,0,1},//1
    {0,0,-1},//2
    {0,1,0},//3
    {0,1,1},//4
    {0,1,-1},//5
    {0,-1,0},//6
    {0,-1,1},//7
    {0,-1,-1},//8
    {1,0,0},//9
    {1,0,1},//10
    {1,0,-1},//11
    {1,1,0},//12
    {1,1,1},//13
    {1,1,-1},//14
    {1,-1,0},//15
    {1,-1,1},//16
    {1,-1,-1},//17
    {-1,0,0},//18
    {-1,0,1},//19
    {-1,0,-1},//20
    {-1,1,0},//21
    {-1,1,1},//22
    {-1,1,-1},//23
    {-1,-1,0},//24
    {-1,-1,1},//25
    {-1,-1,-1},//26
}

//описывает сегмент в последовательной версии
class Segment
{
public:
    int countVoxel;//количество точек всегменте
    int* voxel;//индексы в общем массиве
    int weightSegment;//вес сегмента(максимальный перепад между точками)
    int valueSegment;//значение в сегменте
    Segment* next;
};

class LayerSegmentsTree
{
    int maxCapacity;//максимальное количество точек в сегментах
    int countSegment;//количество сегментов
    Segment* segment;//ссылка на сегменты
    LayerSegmentsTree* up;//вверх дерева
    LayerSegmentsTree* down;//вниз дерева
    int maxValueSegment;//максимальное значение сегментов
    Segment* oldSegment;//ссылка на последний сегмент
};

//хранилище сегментов разных размеров
class SegmentsTree
{
public:
    int countLayer;//количество уровней
    LayerSegmentsTree* root;//корень
};