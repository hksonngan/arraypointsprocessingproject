#include "stdafx.h"
#include "Graph.h"
#include <math.h>
#include <stack>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

//индексы смещения к соседям
char relativeIndexMatrix[27][3] = {//i,j,k
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
};

//Voxel
Voxel::Voxel()
{
	index = 0;
	next = 0;
	segment = 0;
}
Voxel::~Voxel()
{
	index = 0;	
	segment = 0;
	next = 0;
}

//Segment
Segment::Segment()
{
	voxel = 0;
	maxWeight = 0;
	minWeight = 0;
	indexSegment = 0;
	next = 0;
}
Segment::~Segment()
{	
	maxWeight = 0;
	minWeight = 0;
	indexSegment = 0;
	voxel = 0;
	next = 0;
}

SegmentStack::SegmentStack(size_t countSegment)
{
	data = new Segment* [countSegment];
	for (size_t i = 0; i < countSegment; i++)
		data[i] = 0;
	count = 0;
	maxCount = countSegment;
}
SegmentStack::~SegmentStack()
{
	clear(0);
}
bool SegmentStack::empty()
{
	return (count == 0);
}
Segment* SegmentStack::top()
{
	return data[count - 1];
}
void SegmentStack::pop()
{
	data[count - 1] = 0;
	count--;
}
void SegmentStack::push(Segment* seg)
{
	data[count] = seg;
	count++;
}
void SegmentStack::clear(size_t countSegment)
{
	delete [] data;
	if (countSegment != 0)
	{
		data = new Segment* [countSegment];
		for (size_t i = 0; i < countSegment; i++)
			data[i] = 0;
		count = 0;
		maxCount = 0;
	}
}

//LayerSegmentsTree
LayerSegmentsTree::LayerSegmentsTree()
{
	maxCapacity = 0;
	segmentCount = 0;
	segment = 0;
	up = 0;
	down = 0;
	segmentCount = 0;
	oldSegment = 0;
	allVoxel = 0;
	segmentsTree = 0;
}
LayerSegmentsTree::~LayerSegmentsTree()
{	
	maxCapacity = 0;
	segmentCount = 0;
	segmentsTree = 0;
	Segment* s = 0;
	Segment* s2 = 0;
	if (segment != 0)
	{
		s = segment->next;
		s2 = segment;

		delete segment;
		s2 = s;
		while (s != 0)
		{
			s = s2->next;
			delete s2;
			s2 = s;
		}
	}
	delete [] allVoxel;
	delete up;
	down = 0;
}

void LayerSegmentsTree::CreateData(size_t* index, size_t count, ScanData* data)
{
	data->scaleX = segmentsTree->scanData->scaleX;
	data->scaleY = segmentsTree->scanData->scaleY;
	data->scaleZ = segmentsTree->scanData->scaleZ;
	data->sizeX = segmentsTree->scanData->sizeX;
	data->sizeY = segmentsTree->scanData->sizeY;
	data->sizeZ = segmentsTree->scanData->sizeZ;
	if (data->data == 0)
		data->data = new short [data->sizeX * data->sizeY * data->sizeZ];
	for (size_t i = 0; i < data->sizeX * data->sizeY * data->sizeZ; i++)
		data->data[i] = 0;

	size_t j = 0;
	Segment* currentSegment = segment;
	Voxel* voxel = 0;
	while ((currentSegment != 0) && (j < count))
	{
		if (currentSegment->indexSegment == index[j])
		{
			voxel = currentSegment->voxel;
			while (voxel != 0)
			{
				data->data[voxel->index] = segmentsTree->scanData->data[voxel->index];
				voxel = voxel->next;
			}
			j++;
		}
		currentSegment = currentSegment->next;
	}    
}

StepLayers::StepLayers()
{
	 count = 0;
	 border = 0;
	 steps = 0;
}
StepLayers::~StepLayers()
{

	if (border != 0)
		delete [] border;
	if (steps != 0)
		delete [] steps;
	count = 0;
}
void StepLayers::Resize(size_t c)
{
	if (border != 0)
		delete [] border;
	if (steps != 0)
		delete [] steps;
	count = c;
	border = new short [count];
	steps = new short [count];
}

//SegmentsTree
SegmentsTree::SegmentsTree()
{
	Initialization();
}

SegmentsTree::SegmentsTree(ScanData* data)
{
	Initialization();
	CreateRoot(data);
}
SegmentsTree::~SegmentsTree()
{
	countLayer = 0;
	step = 50;
	maxValue = 32760;
	minValue = -32760;
	minCountVoxelInSegment = 0;
	scanData = 0;
	delete root;
}

void SegmentsTree::Initialization()
{
	countLayer = 0;
	root = 0;
	step = 50;
	maxValue = 32760;
	minValue = -32760;
	minCountVoxelInSegment = 0;
	errorCode = 0;
	isConstStep = 0;
	steps = 0;
}

void SegmentsTree::CreateRoot(ScanData* data)
{
	scanData = data;
	dimension = scanData->sizeX * scanData->sizeY * scanData->sizeZ; //количество вокселей
	root = new LayerSegmentsTree();
	root->allVoxel = new Voxel [data->sizeX*data->sizeY*data->sizeZ];

	Segment* segment = new Segment();
	Segment* oldSegment = segment;
	root->allVoxel[0].index = 0;
	root->allVoxel[0].next = 0;
	root->allVoxel[0].segment = segment;

	root->segment = segment;
	segment->voxel = &root->allVoxel[0];
	segment->indexSegment = 0;
	segment->maxWeight = data->data[0];
	segment->minWeight = data->data[0];
	segment->сapacity = 1;

	for (size_t i = 1; i < data->sizeX*data->sizeY*data->sizeZ; i++)
	{
		segment = new Segment();
		oldSegment->next = segment;
		root->allVoxel[i].index = i;
		root->allVoxel[i].next = 0;
		root->allVoxel[i].segment = segment;
		segment->voxel = &root->allVoxel[i];
		segment->indexSegment = i;
		segment->maxWeight = data->data[i];
		segment->minWeight = data->data[i];
		segment->сapacity = 1;
		oldSegment = segment;
	}
	countLayer++;     
	root->segmentCount = data->sizeX*data->sizeY*data->sizeZ - 1;
	root->maxCapacity = 1;
	root->oldSegment = oldSegment;
	root->down = 0;
	root->up = 0;
	root->segmentsTree = this;
}

LayerSegmentsTree* SegmentsTree::GetOldLayer()
{
	LayerSegmentsTree* layer = root;
	while (layer->up != 0)
		layer = layer->up;
	return layer;
}

size_t SegmentsTree::DeterminationAdjacentsOldSegment(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
													  bool* isNotSegmentWorked, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w, 
													  size_t maxVoxelVisit, SegmentStack* stackSegments)
{
	short stepCurrent = step;
	if (!isConstStep)
	{
		int indexStep = 0;
		for (int i = 0; i < steps->count; i++)
		{
			if (w < steps->border[i])
			{
				stepCurrent = steps->steps[i];
				break;
			}
		}		
	}

	stackSegments->push(segmentCurrent);

	size_t adjacentsCount = 0; 
	size_t visitCount = 0;
	size_t adjacentsVoxelCount = 0;

	size_t indexSegmentCurrent = segmentCurrent->indexSegment;
	isNotVisit[segmentCurrent->indexSegment] = false;

	bool isStop = false;
	while((!stackSegments->empty()) && (!isStop))
	{
		segmentCurrent = stackSegments->top();
		stackSegments->pop();

		Voxel* currentVoxel = segmentCurrent->voxel;
		size_t indexVoxel = 0;

		while(currentVoxel != 0)
		{
			for(size_t k = 1; k < 27; k++)
			{
				indexVoxel = currentVoxel->index + relativeIndexMatrix[k][0] + relativeIndexMatrix[k][1] * scanData->sizeX +
					relativeIndexMatrix[k][2] * scanData->sizeX * scanData->sizeY;
				if ((indexVoxel >= 0) && (indexVoxel < scanData->sizeX * scanData->sizeY * scanData->sizeZ))
				{
					Segment* segment = oldLayer->allVoxel[indexVoxel].segment;
					size_t indexiSegmentAdjacent =  segment->indexSegment;

					if (isNotSegmentWorked[indexiSegmentAdjacent])
					{
						if (isNotVisit[indexiSegmentAdjacent])
						{
							isNotVisit[indexiSegmentAdjacent] = false;
							visitSegment[visitCount] = indexiSegmentAdjacent;
							visitCount++;                            
							if (abs(w - segment->maxWeight) <= stepCurrent)
							{
								segmentAdjacents[countSegmentAdjacents] = segment;
								countSegmentAdjacents++;
								adjacentsCount++;
								adjacentsVoxelCount += segment->сapacity;
								if (adjacentsVoxelCount >= maxVoxelVisit)
									isStop = true;
								else
									stackSegments->push(segment);
							}
						}
					}
				}

			}
			currentVoxel = currentVoxel->next;
		}
	}   
	while (!stackSegments->empty())
		stackSegments->pop();

	for (size_t k = 0; k < visitCount; k++)
	{
		isNotVisit[visitSegment[k]] = true;
		visitSegment[k] = 0;
	}
	isNotVisit[indexSegmentCurrent] = true;

	return adjacentsVoxelCount;
}

void SegmentsTree::DeterminationAdjacentsNewSegment(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, LayerSegmentsTree* newLayer, 
													bool* isNotSegmentWorked, size_t* indexNewSegment, bool* isNotVisit, size_t* visitSegment, 
													Segment*& minimalSegment)
{
	size_t adjacentsCount = 0; 
	size_t visitCount = 0;
	size_t adjacentsVoxelCount = 0;

	bool isStop = false;

	segmentCurrent = segmentCurrent;
	isNotVisit[segmentCurrent->indexSegment] = false;

	Voxel* currentVoxel = segmentCurrent->voxel;
	size_t indexVoxel = 0;

	size_t mins = dimension + 3;

	while(currentVoxel != 0)
	{
		for(size_t k = 1; k < 27; k++)
		{
			indexVoxel = currentVoxel->index + relativeIndexMatrix[k][0] + relativeIndexMatrix[k][1] * scanData->sizeX +
				relativeIndexMatrix[k][2] * scanData->sizeX * scanData->sizeY;
			if ((indexVoxel >= 0) && (indexVoxel < scanData->sizeX * scanData->sizeY * scanData->sizeZ))
			{
				Segment* segmentA = oldLayer->allVoxel[indexVoxel].segment;
				size_t indexiSegmentAdjacent =  segmentA->indexSegment;
				if (newLayer->allVoxel[indexNewSegment[segmentA->indexSegment]].segment != 0)
				{
					Segment* segmentB = newLayer->allVoxel[indexNewSegment[segmentA->indexSegment]].segment;
					if (!isNotSegmentWorked[indexiSegmentAdjacent])
					{
						if (isNotVisit[segmentB->indexSegment])
						{
							{
								isNotVisit[segmentB->indexSegment] = false;
								visitSegment[visitCount] = segmentB->indexSegment;
								visitCount++;                            
								{
									if ((segmentB->сapacity < mins) && (segmentB->сapacity >= minCountVoxelInSegment))
									{
										minimalSegment = segmentB;
										mins = segmentB->сapacity;
									}
								}
							}
						}
					}
				}
			}

		}
		currentVoxel = currentVoxel->next;
	}

	for (size_t k = 0; k < visitCount; k++)
	{
		isNotVisit[visitSegment[k]] = true;
		visitSegment[k] = 0;
	}
}

void SegmentsTree::MergeVoxel(size_t countSegmentAdjacents, size_t& newCountVoxel, size_t maxCountVoxel, Segment** segmentAdjacents, 
							  short& maxWeight, short& minWeight, size_t& countVoxel, LayerSegmentsTree* newLayer, Voxel*& oldVoxel,
							  bool* isNotSegmentWorked, size_t& countSegmentWorked, size_t startIndex)
{
	Segment* segmentCurrent = 0;
	Voxel* voxelCurrent = 0;
	for (size_t segmentAdjacent = startIndex; ((segmentAdjacent < countSegmentAdjacents) && ((countVoxel + newCountVoxel) < maxCountVoxel)); segmentAdjacent++)
	{
		segmentCurrent = segmentAdjacents[segmentAdjacent];
		maxWeight = max(segmentCurrent->maxWeight, maxWeight);
		minWeight = min(segmentCurrent->minWeight, minWeight);

		voxelCurrent = segmentCurrent->voxel;
		oldVoxel->next = &newLayer->allVoxel[voxelCurrent->index];

		while(voxelCurrent->next != 0)
		{
			newLayer->allVoxel[voxelCurrent->index].index = voxelCurrent->index;
			newLayer->allVoxel[voxelCurrent->index].segment = 0;
			newLayer->allVoxel[voxelCurrent->index].next = &newLayer->allVoxel[voxelCurrent->next->index];
			voxelCurrent = voxelCurrent->next;
			newCountVoxel++;
		}
		newLayer->allVoxel[voxelCurrent->index].index = voxelCurrent->index;
		newLayer->allVoxel[voxelCurrent->index].segment = 0;
		oldVoxel = &newLayer->allVoxel[voxelCurrent->index];

		isNotSegmentWorked[segmentCurrent->indexSegment] = false;
		newCountVoxel++;
		countSegmentWorked++;

		segmentAdjacents[segmentAdjacent] = NULL;
	}
}

void SegmentsTree::CreateNewSegment(LayerSegmentsTree* oldLayer, LayerSegmentsTree* newLayer, size_t& maxCountVoxel, Voxel* oldVoxel, 
									Segment* segment, size_t* indexNewSegment, size_t& countVoxel, short& maxWeight, short& minWeight)
{
	//создание нового сегмента

	maxCountVoxel = max(maxCountVoxel, countVoxel);

	//создание нового сегмента
	if (newLayer->segment != 0)
	{
		newLayer->oldSegment->next = new Segment();
		newLayer->oldSegment = newLayer->oldSegment->next;
	}
	else
	{
		newLayer->segment = new Segment();
		newLayer->oldSegment = newLayer->segment;
	}

	//инициализация нового сегмента
	newLayer->oldSegment->indexSegment = newLayer->segmentCount;
	newLayer->segmentCount++;
	newLayer->oldSegment->voxel = &newLayer->allVoxel[segment->voxel->index];
	oldVoxel->next = NULL;
	Voxel* cv = &newLayer->allVoxel[segment->voxel->index];
	while(cv != 0)
	{
		cv->segment = newLayer->oldSegment;
		indexNewSegment[oldLayer->allVoxel[cv->index].segment->indexSegment] = newLayer->oldSegment->voxel->index;
		cv = cv->next;
	}


	newLayer->oldSegment->сapacity = countVoxel;
	newLayer->oldSegment->maxWeight = maxWeight;
	newLayer->oldSegment->minWeight = minWeight;
}

void SegmentsTree::AddVoxelToOldSegment(Segment* segment, Segment* minimalSegment, LayerSegmentsTree* newLayer, LayerSegmentsTree* oldLayer, 
										Voxel*& oldVoxel, size_t* indexNewSegment, size_t& countVoxel, short& maxWeight, short& minWeight)
{
	Voxel* oldCurVoxel = minimalSegment->voxel;
	while (oldCurVoxel->next != 0)
	{
		oldCurVoxel = oldCurVoxel->next;
	}

	Voxel* cv = &newLayer->allVoxel[segment->voxel->index];

	oldCurVoxel->next = &newLayer->allVoxel[segment->voxel->index];
	oldVoxel->next = NULL;
	while(cv != 0)
	{
		cv->segment = minimalSegment;
		indexNewSegment[oldLayer->allVoxel[cv->index].segment->indexSegment] = minimalSegment->voxel->index;
		cv = cv->next;
	}
	minimalSegment->maxWeight = max(maxWeight, minimalSegment->maxWeight);
	minimalSegment->minWeight = min(minWeight, minimalSegment->minWeight);
	minimalSegment->сapacity += countVoxel;
}


void SegmentsTree::ProcessingSegment(	short& maxWeight,
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
LayerSegmentsTree* oldLayer,
LayerSegmentsTree* newLayer 
)
{
	if (isNotSegmentWorked[indexSegments])
	{  
		//если текущий сегмент не обработан
		step = initStep;
		countVoxel = 0;

		//подготовка списка соседей
		countSegmentAdjacents = 1;
		segmentAdjacents[0] = segment;
		//определяем соседей
		DeterminationAdjacentsOldSegment(oldLayer, segment, segmentAdjacents, isNotSegmentWorked, 
			countSegmentAdjacents, isNotVisit, visitSegment, segment->maxWeight, dimension, segmentStack);

		//заполнение вокселей сегмента и определение веса сегмента как максимума весов
		Voxel* oldVoxel = 0;
		oldVoxel = &newLayer->allVoxel[segment->voxel->index];
		Voxel* voxelCurrent = 0;
		maxWeight = segment->maxWeight;
		minWeight = segment->minWeight;
		newCountVoxel = 0;
		//объединяем воксели соседних сегментов
		MergeVoxel(countSegmentAdjacents, newCountVoxel, dimension, segmentAdjacents, maxWeight, 
			minWeight, countVoxel, newLayer, oldVoxel, isNotSegmentWorked, countSegmentWorked, 0);
		countVoxel += newCountVoxel;

		for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
			segmentAdjacents[segmentAdjacent] = NULL;

		sumCountVoxel += countVoxel;
		int t = 0;
		newCountVoxel = 0;
		bool isStop = false;

		if (countVoxel < minCountVoxelInSegment)
		{
			//количество вокселей недостаточно
			//определяем минимальный новый соседний сегмент
			Segment* minimalSegment = 0;
			DeterminationAdjacentsNewSegment(oldLayer, segment, newLayer, isNotSegmentWorked, indexNewSegment, isNotVisit, visitSegment, minimalSegment);
			if (minimalSegment != 0)
			{
				//нашелся уже существующий сосед
				//шаг с которым получаем минимальный новый сегмент
				step = abs(minimalSegment->maxWeight - segment->maxWeight);

				newCountVoxel = 0;
				countSegmentAdjacents = 1;
				segmentAdjacents[0] = segment;
				//определяем соседей с выбранным шагом
				size_t adjacentVoxelCount = DeterminationAdjacentsOldSegment(oldLayer, segment, segmentAdjacents, isNotSegmentWorked, 
					countSegmentAdjacents, isNotVisit, visitSegment, segment->maxWeight, minCountVoxelInSegment + 2, segmentStack);
				int f = 0;
				if ((countVoxel + adjacentVoxelCount) >= minCountVoxelInSegment)
				{
					//если вокселей достаточно - объеденяем в один сегмент
					voxelCurrent = 0;

					MergeVoxel(countSegmentAdjacents, newCountVoxel, minCountVoxelInSegment, segmentAdjacents, maxWeight, 
						minWeight, countVoxel, newLayer, oldVoxel, isNotSegmentWorked, countSegmentWorked, 1);

					countVoxel += newCountVoxel;
					sumCountVoxel += newCountVoxel;

					CreateNewSegment(oldLayer, newLayer, maxCountVoxel, oldVoxel, segment, indexNewSegment, countVoxel, maxWeight, minWeight);
					f += 1;
				}
				//зачистка списка
				for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
					segmentAdjacents[segmentAdjacent] = NULL;
				if ((countVoxel + adjacentVoxelCount) < minCountVoxelInSegment)
				{
					//если вокселей меньше - добавляем текущий сегмент в минимальный из уже созданных
					AddVoxelToOldSegment(segment, minimalSegment, newLayer, oldLayer, oldVoxel, indexNewSegment, countVoxel, maxWeight, minWeight);
					f += 1;
				}
				if (f != 1)
					int errorCode = 1;
			}
			else
			{				
				//не существует созданных соседей
				//объеденяем текущий с какими нибудь соседями, что бы добрать нужное число 
				bool initIsConstStep = isConstStep;
				while ((countVoxel < minCountVoxelInSegment) && (!isStop))
				{
					//если 
					newCountVoxel = 0;

					countSegmentAdjacents = 1;

					segmentAdjacents[0] = segment;
					//определяем соседей

					DeterminationAdjacentsOldSegment(oldLayer, segment, segmentAdjacents, isNotSegmentWorked, 
						countSegmentAdjacents, isNotVisit, visitSegment, segment->maxWeight, minCountVoxelInSegment + 2, segmentStack);


					voxelCurrent = 0;

					MergeVoxel(countSegmentAdjacents, newCountVoxel, minCountVoxelInSegment, segmentAdjacents, maxWeight, 
						minWeight, countVoxel, newLayer, oldVoxel, isNotSegmentWorked, countSegmentWorked, 1);

					for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
						segmentAdjacents[segmentAdjacent] = NULL;
					countVoxel += newCountVoxel;
					sumCountVoxel += newCountVoxel;
					if (countSegmentAdjacents == 1)
					{
						//если соседей не найдено - увеличиваем шаг
						if (step < short(floor(maxValue / float(multiplierIncrementStep))))
							step = step * multiplierIncrementStep;
						else
							if (step == maxValue)
							{
								isStop = true;
							}
							else
								step = maxValue;
					}

					t++;
				}
				step = initStep;
				isConstStep = initIsConstStep;
				CreateNewSegment(oldLayer, newLayer, maxCountVoxel, oldVoxel, segment, indexNewSegment, countVoxel, maxWeight, minWeight);

			}				
		}
		else
			CreateNewSegment(oldLayer, newLayer, maxCountVoxel, oldVoxel, segment, indexNewSegment, countVoxel, maxWeight, minWeight);

	}
	segment = segment->next;
	indexSegments++;
}

LayerSegmentsTree* SegmentsTree::CreateNewLayer(size_t indexStartVoxel)
{
	LayerSegmentsTree* oldLayer = GetOldLayer();//последний уровень сегментации

	//проверка что на предыдущем уровне не были потерекны воксели
	Segment* oldSegment = oldLayer->segment;
	Voxel* oldVoxel = oldSegment->voxel;
	size_t countOldVoxel = 0;
	while (oldSegment != 0)
	{
		oldVoxel = oldSegment->voxel;
		while (oldVoxel != 0)
		{
			countOldVoxel++;
			oldVoxel = oldVoxel->next;
		}
		oldSegment = oldSegment->next;
	}
	if (countOldVoxel != dimension)
		errorCode = 1;

	//мнициализация нового сегмента
	LayerSegmentsTree* newLayer = new LayerSegmentsTree();
	oldLayer->up = newLayer;
	newLayer->down = oldLayer;	
	newLayer->allVoxel = new Voxel [dimension];
	newLayer->maxCapacity = 0;
	newLayer->segmentCount = 0;
	newLayer->segment = 0;
	newLayer->oldSegment = 0;
	newLayer->segmentsTree = this;

	//вспомогаельные данные
	short maxWeight = 0;//максимальный вес текущего сегмента
	short minWeight = 0;//минимальный вес текущего сегмента
	size_t countVoxel = 0;//количество вокселей  текущего сегмента
	size_t maxCountVoxel = 0;//максимально количество вокселей в егментах на текущем уравне
	size_t sumCountVoxel = 0;//суммарное количество вокселей
	size_t countSegmentWorked = 0;//количество сегментов обработанных при обходе в глобальном цикле 
	size_t countSegmentAdjacents = 0;//количество соседей у текущего вокселя
	size_t newCountVoxel = 0;//количество вокселей добавляемых при недостаточном размере образуемого сегмента
	Segment** segmentAdjacents = new Segment* [oldLayer->segmentCount + 2];//список соседных сегментов
	bool* isNotVisit = new bool [oldLayer->segmentCount + 2];//не посещен ли сегмент при определение соседей
	size_t* visitSegment = new size_t [oldLayer->segmentCount + 2];//индекс сегментов посещенных при определение соседей
	bool* isNotSegmentWorked = new bool [oldLayer->segmentCount + 2];//не обработан ли сегмент в главном цикле
	size_t* indexNewSegment = new size_t [oldLayer->segmentCount + 2];//индекс нового сегмента в который перешел(при слияние или добавление) старый
	SegmentStack* segmentStack = new SegmentStack(oldLayer->segmentCount + 2);//стек сегментов при поиске соседей

	for (size_t i = 0; i < oldLayer->segmentCount + 2; i++)
	{
		segmentAdjacents[i] = 0;
		isNotVisit[i] = true;
		visitSegment[i] = 0;
		isNotSegmentWorked[i] = true;
		indexNewSegment[i] = i;
	}

	short initStep = step;	//изначальный шаг
	indexSegments = oldLayer->allVoxel[indexStartVoxel].segment->indexSegment;
	Segment* segment = oldLayer->allVoxel[indexStartVoxel].segment;//текущий обрабатываемый сегмент

	//основной цикл по сегментам
	while (segment != 0)
	{		
		ProcessingSegment(maxWeight, minWeight, countVoxel, maxCountVoxel, sumCountVoxel, countSegmentWorked,
			countSegmentAdjacents, newCountVoxel, segmentAdjacents, isNotVisit, visitSegment, isNotSegmentWorked,
			 indexNewSegment, segmentStack, initStep, segment, oldLayer, newLayer);
		if ((segment == 0) && (countSegmentWorked < oldLayer->segmentCount))
		{
			indexSegments = 0;
			segment = oldLayer->segment;
		}
	}
	newLayer->maxCapacity = maxCountVoxel;

	//проверка что не потеряли воксели
	Segment* newSegment = newLayer->segment;
	Voxel* newVoxel = newSegment->voxel;
	size_t c = 0;
	while (newSegment != 0)
	{
		newVoxel = newSegment->voxel;
		while (newVoxel != 0)
		{
			c++;
			if (newVoxel->segment->indexSegment != newSegment->indexSegment)
				errorCode = 3;
			newVoxel = newVoxel->next;
		}
		newSegment = newSegment->next;
	}
	if (c != dimension)
		int errorCode = 2;

	delete [] segmentAdjacents;
	delete [] isNotVisit;
	delete [] isNotSegmentWorked;
	delete [] visitSegment;
	delete [] indexNewSegment;
	delete segmentStack;

	step = initStep;

	return newLayer;
}