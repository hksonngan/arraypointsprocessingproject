#pragma once
#include "..\ScanData.h"
#include <list>
#include <iostream>


class Voxel2
{
public:
	size_t index;
	Voxel2* next;

	Voxel2();
};

class SegmentsTree2;

class LayerSegmentsTree2
{
public:
	size_t maxCapacity;//������������ ���������� ����� � ���������
	LayerSegmentsTree2* up;//����� ������
	LayerSegmentsTree2* down;//���� ������
	size_t segmentCount;//���������� ���������
	SegmentsTree2* segmentsTree;//����� ���������

	size_t* indexSegments;//������ ��������� � �������
	Voxel2* indexVoxel;//������� �������� � �������� ��������
	size_t* startIndexVoxel;//������ ������ �������� ��������� � indexVoxel
	size_t* countVoxel;//���������� �������� � ���������
	short* weightSegment;//��� ��������(������������ ������� ����� �������)

	LayerSegmentsTree2();
	void CreateData(size_t* index, size_t count, ScanData* data);




};

typedef void (funct)(char* str);

//��������� ��������� ������ ��������
class SegmentsTree2
{
public:
	short maxValue;
	size_t countLayer;//���������� �������
	LayerSegmentsTree2* root;//������
	ScanData* scanData; //��������� �� �������� ������
	short step;
	size_t indexSegments;

	//�����������
	SegmentsTree2();
	SegmentsTree2(ScanData* data);

	//������� ������
	void CreateRoot(ScanData* data);
	//���� ������� ����
	LayerSegmentsTree2* GetOldLayer();


void Kernel(size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents);


	//������� ����� ����
	LayerSegmentsTree2* CreateNewLayer();

	////���������� �������� ��������
	////void DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
	////	bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w);

};

