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
//��������� �������
class Voxel
{
public:
    size_t index;
    Voxel* next;
    Segment* segment;

    Voxel();
};

//��������� ������� � ���������������� ������
class Segment
{
public:
    size_t �apacity;//���������� ������
    Voxel* voxel;//������� � ����� �������
    short weightSegment;//��� ��������(������������ ������� ����� �������)
    size_t indexSegment;//������ � ��������
    Segment* next;

    Segment();
};

class SegmentsTree;

class LayerSegmentsTree
{
public:
    size_t maxCapacity;//������������ ���������� ����� � ���������
    Segment* segment;//������ �� ��������
    LayerSegmentsTree* up;//����� ������
    LayerSegmentsTree* down;//���� ������
    size_t segmentCount;//���������� ���������
    Segment* oldSegment;//������ �� ��������� �������
    SegmentsTree* segmentsTree;//����� ���������
    Voxel* allVoxel;//��������� �� ������ ��������

    LayerSegmentsTree();

    ScanData* CreateData(size_t* index, size_t count);

};

typedef void (funct)(char* str);

//��������� ��������� ������ ��������
class SegmentsTree
{
public:
    size_t countLayer;//���������� �������
    LayerSegmentsTree* root;//������
    ScanData* scanData; //��������� �� �������� ������
    short step;
    int indexSegments;

    //�����������
    SegmentsTree();
    SegmentsTree(ScanData* data);

    //������� ������
    void CreateRoot(ScanData* data);
    //���� ������� ����
    LayerSegmentsTree* GetOldLayer();
    //���������� �������� ��������
    void DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
        bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w);
    //������� ����� ����
    void CreateNewLayer();
};

