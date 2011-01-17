#pragma once
#include "..\ScanData.h"
#include <list>
#include <iostream>

class Segment;
//��������� �������
class Voxel
{
public:
    size_t index;//������ �������
    Voxel* next;//��������� �������
    Segment* segment;//������� � �������� ���� ������� �����������

    Voxel();
	~Voxel();
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
	~Segment();
};

class SegmentsTree;
//���� ���������
class SegmentStack
{
public:
	Segment** data;//������ �� ��������
	size_t count;//������� ����������
	size_t maxCount;//������������ ����������

	//�����������
	SegmentStack(size_t countSegment);
	~SegmentStack();

	//�������� �� ������� ������
	bool empty();
	//���������� ������� �������
	Segment* top();
	//������� ������� ������� �� ������
	void pop();
	//�������� ������� �� �������
	void push(Segment* seg);
	//������� ����� � ��������� ������
	void clear(size_t countSegment);
	
};

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

	//�����������
    LayerSegmentsTree();
	~LayerSegmentsTree();

	//��������� ������ � ������������ � ���������� ����������
    void CreateData(size_t* index, size_t count, ScanData* data);

};

class StepLayers
{
public:
	size_t count;
	short* border;
	short* steps;


	StepLayers();
	~StepLayers();
	void Resize(size_t c);
};

//��������� ��������� ������ ��������
class SegmentsTree
{
public:
    size_t countLayer;//���������� �������
    LayerSegmentsTree* root;//������
    ScanData* scanData; //��������� �� �������� ������
    short step;//��� �����������(����� ��������)
    size_t indexSegments;//������ ��������������� ��������
	size_t minCountVoxelInSegment;//����������� ���������� �������� � ��������
	short multiplierIncrementStep;//��������� ��� ���������� ���� �����������
	int errorCode; 
	bool isConstStep;
	StepLayers* steps;

    //������������
    SegmentsTree();
    SegmentsTree(ScanData* data);
	~SegmentsTree();

    //������� ������
    void CreateRoot(ScanData* data);
    //���� ������� ����
    LayerSegmentsTree* GetOldLayer();
	//������� ����� ����
    LayerSegmentsTree* CreateNewLayer(size_t indexStartVoxel = 0);

protected:
	short maxValue;
	short minValue;
	size_t dimension;

	//������������� ����������
	void Initialization();
	//���������� �������� �������� ������� ����
	size_t DeterminationAdjacentsOldSegment(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
		bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w, size_t maxVoxelVisit, 
		SegmentStack* stackSegments);
	//����������� ������� �� ����� ������
	void DeterminationAdjacentsNewSegment(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, LayerSegmentsTree* newLayer, 
		bool* isNotSegmentVisit, size_t* indexNewSegment, bool* isNotVisit, size_t* visitSegment, Segment*& minimalSegment);
	//��������� ������� ���������� ���������
	void MergeVoxel(size_t countSegmentAdjacents, size_t& newCountVoxel, size_t maxCountVoxel, Segment** segmentAdjacents, 
		short& maxWeight, short& minWeight, size_t& countVoxel, LayerSegmentsTree* newLayer, Voxel*& oldVoxel,
		bool* isNotSegmentVisit, size_t& countSegmentVisit, size_t startIndex);
	//������� ����� �������
	void CreateNewSegment(LayerSegmentsTree* oldLayer, LayerSegmentsTree* newLayer, size_t& maxCountVoxel, Voxel* oldVoxel, 
		Segment* segment, size_t* indexNewSegment, size_t& countVoxel, short& maxWeight, short& minWeight);
	//��������� ������� � ��� ��������� ������� ������ ����
	void AddVoxelToOldSegment(Segment* segment, Segment* minimalSegment, LayerSegmentsTree* newLayer, LayerSegmentsTree* oldLayer, 
		Voxel*& oldVoxel, size_t* isNewSegment, size_t& countVoxel, short& maxWeight, short& minWeight);
	//�������� ��������� �����
	void ProcessingSegment(	short& maxWeight,
		short& minWeight,
		size_t& countVoxel,
		size_t& maxCountVoxel,
		size_t& sumCountVoxel,
		size_t& countSegmentWorked,
		size_t& countSegmentAdjacents,
		size_t& newCountVoxel,
		Segment** segmentAdjacents,
		bool* isNotVisit,
		size_t* visitSegment,
		bool* isNotSegmentWorked,
		size_t* indexNewSegment,
		SegmentStack*& segmentStack,
		short& initStep,
		Segment*& segment,
		LayerSegmentsTree* oldSegment,
		LayerSegmentsTree* newLayer 
		);
};

