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
	size_t maxCapacity;//максимальное количество точек в сегментах
	LayerSegmentsTreeGPU* up;//вверх дерева
	LayerSegmentsTreeGPU* down;//вниз дерева
	size_t segmentCount;//количество сегментов
	SegmentsTreeGPU* segmentsTree;//класс хранилище

	size_t* indexSegments;//индекс симплекса у вокселя
	VoxelGPU* indexVoxel;//индексы входящих в сегменты вокселей
	size_t* startIndexVoxel;//индекс начала вокселей сегментов в indexVoxel
	size_t* countVoxel;//количество вокселей в сегментах
	short* maxWeight;//вес сегмента(максимальное значение плотности)
	short* minWeight;

	LayerSegmentsTreeGPU();
	~LayerSegmentsTreeGPU();

	void CreateData(size_t* index, size_t count, ScanData* data);




};

typedef void (funct)(char* str);

//хранилище сегментов разных размеров
class SegmentsTreeGPU
{
public:
	short maxValue;
	size_t countLayer;//количество уровней
	LayerSegmentsTreeGPU* root;//корень
	ScanData* scanData; //указатель на исходные данные
	short step;
	size_t indexSegments;

	//конструктор
	SegmentsTreeGPU();
	SegmentsTreeGPU(ScanData* data);
	~SegmentsTreeGPU();

	//создать корень
	void CreateRoot(ScanData* data);
	//дать верхний слой
	LayerSegmentsTreeGPU* GetOldLayer();

	//последовательный аналог ядра
	void Kernel(size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents);


	//создать новый слой
	LayerSegmentsTreeGPU* CreateNewLayer();

	////определить соседние сегменты
	////void DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
	////	bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w);

};

