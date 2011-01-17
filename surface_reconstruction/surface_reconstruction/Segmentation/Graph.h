#pragma once
#include "..\ScanData.h"
#include <list>
#include <iostream>

class Segment;
//описывает воксель
class Voxel
{
public:
    size_t index;//индекс вокселя
    Voxel* next;//следующий воксель
    Segment* segment;//сегмент к которому этот воксель принадлежит

    Voxel();
	~Voxel();
};

//описывает сегмент в последовательной версии
class Segment
{
public:
    size_t сapacity;//количество тогчек
    Voxel* voxel;//индексы в общем массиве
    short maxWeight;//максимальнывй вес сегмента(максимальное значение плотности)
	short minWeight;
    size_t indexSegment;//индекс в сегменте
    Segment* next;

    Segment();
	~Segment();
};

class SegmentsTree;
//стек сегментов
class SegmentStack
{
public:
	Segment** data;//ссылки на сегменты
	size_t count;//текущее количество
	size_t maxCount;//максимальное количество

	//конструктор
	SegmentStack(size_t countSegment);
	~SegmentStack();

	//проверка на пустоту списка
	bool empty();
	//возвращает верхний сегмент
	Segment* top();
	//удаляет верхний сегмент из списка
	void pop();
	//помещает сегмент на вершину
	void push(Segment* seg);
	//очистка стека и выделение помяти
	void clear(size_t countSegment);
	
};

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

	//конструктор
    LayerSegmentsTree();
	~LayerSegmentsTree();

	//заполнить данные в соответствие с выбранными сегментами
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

//хранилище сегментов разных размеров
class SegmentsTree
{
public:
    size_t countLayer;//количество уровней
    LayerSegmentsTree* root;//корень
    ScanData* scanData; //указатель на исходные данные
    short step;//шаг сегментации(порог значений)
    size_t indexSegments;//индекс обрабатываемого сегмента
	size_t minCountVoxelInSegment;//минимальное количество вокселей в сегменте
	short multiplierIncrementStep;//множитель при увеличение шага сегментации
	int errorCode; 
	bool isConstStep;
	StepLayers* steps;

    //конструкторы
    SegmentsTree();
    SegmentsTree(ScanData* data);
	~SegmentsTree();

    //создать корень
    void CreateRoot(ScanData* data);
    //дать верхний слой
    LayerSegmentsTree* GetOldLayer();
	//создать новый слой
    LayerSegmentsTree* CreateNewLayer(size_t indexStartVoxel = 0);

protected:
	short maxValue;
	short minValue;
	size_t dimension;

	//инициализация переменных
	void Initialization();
	//определить соседние сегменты старого слоя
	size_t DeterminationAdjacentsOldSegment(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
		bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w, size_t maxVoxelVisit, 
		SegmentStack* stackSegments);
	//определение соседей но новом уравне
	void DeterminationAdjacentsNewSegment(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, LayerSegmentsTree* newLayer, 
		bool* isNotSegmentVisit, size_t* indexNewSegment, bool* isNotVisit, size_t* visitSegment, Segment*& minimalSegment);
	//объденяет воксели нескольких сегментов
	void MergeVoxel(size_t countSegmentAdjacents, size_t& newCountVoxel, size_t maxCountVoxel, Segment** segmentAdjacents, 
		short& maxWeight, short& minWeight, size_t& countVoxel, LayerSegmentsTree* newLayer, Voxel*& oldVoxel,
		bool* isNotSegmentVisit, size_t& countSegmentVisit, size_t startIndex);
	//создать новый сегмент
	void CreateNewSegment(LayerSegmentsTree* oldLayer, LayerSegmentsTree* newLayer, size_t& maxCountVoxel, Voxel* oldVoxel, 
		Segment* segment, size_t* indexNewSegment, size_t& countVoxel, short& maxWeight, short& minWeight);
	//добовляет воксели в уже созданный сегмент нового слоя
	void AddVoxelToOldSegment(Segment* segment, Segment* minimalSegment, LayerSegmentsTree* newLayer, LayerSegmentsTree* oldLayer, 
		Voxel*& oldVoxel, size_t* isNewSegment, size_t& countVoxel, short& maxWeight, short& minWeight);
	//итерация основного цикла
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

