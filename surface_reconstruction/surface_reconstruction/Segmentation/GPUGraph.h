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
	size_t maxCapacity;//максимальное количество точек в сегментах
	LayerSegmentsTree2* up;//вверх дерева
	LayerSegmentsTree2* down;//вниз дерева
	size_t segmentCount;//количество сегментов
	SegmentsTree2* segmentsTree;//класс хранилище

	size_t* indexSegments;//индекс симплекса у вокселя
	Voxel2* indexVoxel;//индексы входящих в сегменты вокселей
	size_t* startIndexVoxel;//индекс начала вокселей сегментов в indexVoxel
	size_t* countVoxel;//количество вокселей в сегментах
	short* weightSegment;//вес сегмента(максимальный перепад между точками)

	LayerSegmentsTree2();
	void CreateData(size_t* index, size_t count, ScanData* data);




};

typedef void (funct)(char* str);

//хранилище сегментов разных размеров
class SegmentsTree2
{
public:
	short maxValue;
	size_t countLayer;//количество уровней
	LayerSegmentsTree2* root;//корень
	ScanData* scanData; //указатель на исходные данные
	short step;
	size_t indexSegments;

	//конструктор
	SegmentsTree2();
	SegmentsTree2(ScanData* data);

	//создать корень
	void CreateRoot(ScanData* data);
	//дать верхний слой
	LayerSegmentsTree2* GetOldLayer();


void Kernel(size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents);


	//создать новый слой
	LayerSegmentsTree2* CreateNewLayer();

	////определить соседние сегменты
	////void DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
	////	bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w);

};

