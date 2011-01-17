#pragma once
#include "..\ScanData.h"
#include <list>
#include <iostream>


class VoxelGPU
{
public:
	size_t index;
	VoxelGPU* next;

	VoxelGPU();
	~VoxelGPU();
};

class SegmentsTreeGPU;

class LayerSegmentsTreeGPU
{
public:
	size_t maxCapacity;//������������ ���������� ����� � ���������
	LayerSegmentsTreeGPU* up;//����� ������
	LayerSegmentsTreeGPU* down;//���� ������
	size_t segmentCount;//���������� ���������
	SegmentsTreeGPU* segmentsTree;//����� ���������

	size_t* indexSegments;//������ ��������� � �������
	VoxelGPU* indexVoxel;//������� �������� � �������� ��������
	size_t* startIndexVoxel;//������ ������ �������� ��������� � indexVoxel
	size_t* countVoxel;//���������� �������� � ���������
	short* maxWeight;//��� ��������(������������ �������� ���������)
	short* minWeight;

	LayerSegmentsTreeGPU();
	~LayerSegmentsTreeGPU();

	void CreateData(size_t* index, size_t count, ScanData* data);




};

typedef void (funct)(char* str);

//��������� ��������� ������ ��������
class SegmentsTreeGPU
{
public:
	short maxValue;
	size_t countLayer;//���������� �������
	LayerSegmentsTreeGPU* root;//������
	ScanData* scanData; //��������� �� �������� ������
	short step;
	size_t indexSegments;

	//�����������
	SegmentsTreeGPU();
	SegmentsTreeGPU(ScanData* data);
	~SegmentsTreeGPU();

	//������� ������
	void CreateRoot(ScanData* data);
	//���� ������� ����
	LayerSegmentsTreeGPU* GetOldLayer();

	//���������������� ������ ����
	void Kernel(size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents);


	//������� ����� ����
	LayerSegmentsTreeGPU* CreateNewLayer();

	////���������� �������� ��������
	////void DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
	////	bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w);

};

