#pragma once
#include "..\ScanData.h"
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
    short maxWeight;//������������� ��� ��������(������������ �������� ���������)
	short minWeight;
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

    void CreateData(size_t* index, size_t count, ScanData* data);

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
    size_t indexSegments;
    size_t countSegments;
	size_t minVoxel;

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
    LayerSegmentsTree* CreateNewLayer();
};

