#include "stdafx.h"
#include "Graph.h"
#include <math.h>
#include <stack>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
//Voxel
Voxel::Voxel()
{
	index = 0;
	next = 0;
	segment = 0;
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

//SegmentsTree
SegmentsTree::SegmentsTree()
{
	countLayer = 0;
	root = 0;
	step = 50;
	countSegments = 0;
	maxValue = 32000;
	minVoxel = 0;
}

SegmentsTree::SegmentsTree(ScanData* data)
{
	countLayer = 0;
	root = 0;
	step = 50;
	countSegments = 0;
	minVoxel = 0;
	maxValue = 32000;
	CreateRoot(data);
}

void SegmentsTree::CreateRoot(ScanData* data)
{
	scanData = data;
	root = new LayerSegmentsTree();
	Segment* segments = new Segment [data->sizeX*data->sizeY*data->sizeZ];
	root->allVoxel = new Voxel [data->sizeX*data->sizeY*data->sizeZ];

	root->allVoxel[0].index = 0;
	root->allVoxel[0].next = 0;
	root->allVoxel[0].segment = &segments[0];

	root->segment = &segments[0];
	segments[0].voxel = &root->allVoxel[0];
	segments[0].indexSegment = 0;
	segments[0].maxWeight = data->data[0];
	segments[0].minWeight = data->data[0];
	segments[0].сapacity = 1;

	for (size_t i = 1; i < data->sizeX*data->sizeY*data->sizeZ; i++)
	{
		segments[i - 1].next = &segments[i];
		root->allVoxel[i].index = i;
		root->allVoxel[i].next = 0;
		root->allVoxel[i].segment = &segments[i];
		segments[i].voxel = &root->allVoxel[i];
		segments[i].indexSegment = i;
		segments[i].maxWeight = data->data[i];
		segments[i].minWeight = data->data[i];
		segments[i].сapacity = 1;

	}
	countLayer++;     
	root->segmentCount = data->sizeX*data->sizeY*data->sizeZ - 1;
	root->maxCapacity = 1;
	root->oldSegment = &segments[data->sizeX*data->sizeY*data->sizeZ - 1];
	root->down = 0;
	root->up = 0;
	root->segmentsTree = this;
	countSegments++;
}

LayerSegmentsTree* SegmentsTree::GetOldLayer()
{
	LayerSegmentsTree* layer = root;
	while (layer->up != 0)
		layer = layer->up;
	return layer;
}

void SegmentsTree::DeterminationAdjacents(LayerSegmentsTree* oldLayer, Segment* segmentCurrent, Segment** segmentAdjacents, 
										  bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w, size_t maxVoxelVisit)
{
	//индексы смещения
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




	std::stack<Segment*> stackSegments;
	stackSegments.push(segmentCurrent);

	size_t adjacentsCount = 0; 
	size_t visitCount = 0;
	size_t adjacentsVoxelCount = 0;

	isNotVisit[segmentCurrent->indexSegment] = false;

	bool isStop = false;
	while((!stackSegments.empty()) && (!isStop))
	{
		segmentCurrent = stackSegments.top();
		stackSegments.pop();

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

					if (isNotSegmentVisit[indexiSegmentAdjacent])
					{
						if (isNotVisit[indexiSegmentAdjacent])
						{
							isNotVisit[indexiSegmentAdjacent] = false;
							visitSegment[visitCount] = indexiSegmentAdjacent;
							visitCount++;                            
							if (abs(w - segment->maxWeight) <= step)
							{
								segmentAdjacents[countSegmentAdjacents] = segment;
								countSegmentAdjacents++;
								adjacentsCount++;
								adjacentsVoxelCount += segment->сapacity;
								if (adjacentsVoxelCount >= maxVoxelVisit)
									isStop = true;
								else
									stackSegments.push(segment);
							}
						}
					}
				}

			}
			currentVoxel = currentVoxel->next;
		}
	}   
	while (!stackSegments.empty())
		stackSegments.pop();

	for (size_t k = 0; k < visitCount; k++)
	{
		isNotVisit[visitSegment[k]] = true;
		visitSegment[visitCount] = 0;
	}
}

LayerSegmentsTree* SegmentsTree::CreateNewLayer(bool isCombineMajorSegment)
{
	countSegments++;
	LayerSegmentsTree* oldLayer = GetOldLayer();

	Segment* segment = oldLayer->segment;

	bool* isNotSegmentVisit = new bool [oldLayer->segmentCount + 2];
	bool* isNewSegment = new bool [oldLayer->segmentCount + 2];
	for (size_t i = 0; i < oldLayer->segmentCount + 2; i++)
	{
		isNotSegmentVisit[i] = true;
		isNewSegment[i] = false;
	}

	LayerSegmentsTree* newLayer = new LayerSegmentsTree();
	oldLayer->up = newLayer;
	newLayer->down = oldLayer;
	size_t dim = scanData->sizeX * scanData->sizeY * scanData->sizeZ;
	newLayer->allVoxel = new Voxel [dim];
	newLayer->maxCapacity = 0;
	newLayer->segmentCount = 0;
	newLayer->segment = 0;
	newLayer->oldSegment = 0;
	newLayer->segmentsTree = this;


	segment = oldLayer->segment;
	indexSegments = 0;
	Segment** segmentAdjacents;

	short maxWeight = 0;
	short minWeight = 0;
	size_t countVoxel = 0;
	size_t maxCountVoxel = 0;
	size_t sumCountVoxel = 0;
	size_t countSegmentVisit = 0;
	size_t countSegmentAdjacents = 0;
	segmentAdjacents = new Segment* [oldLayer->segmentCount];
	bool* isNotVisit = new bool [oldLayer->segmentCount + 2];
	size_t* visitSegment = new size_t [oldLayer->segmentCount];

	for (size_t k = 0; k < oldLayer->segmentCount; k++)
	{
		segmentAdjacents[k] = 0;
		isNotVisit[k] = true;
		visitSegment[k] = 0;
	}

	size_t countSegmentNotVisit = oldLayer->segmentCount -  countSegmentVisit;
	short oldStep = step;
	bool isHaveMinorSegment = false;
	while (segment != 0)
	{		
		if ((isCombineMajorSegment == true) || ((isCombineMajorSegment == false) && (segment->сapacity < minVoxel)))			
			if (isNotSegmentVisit[indexSegments])
			{            
				step = oldStep;
				countVoxel = 0;
				//подготовка списка соседей

				if ((countSegmentNotVisit / 2) > oldLayer->segmentCount -  countSegmentVisit)
				{
					countSegmentNotVisit = oldLayer->segmentCount -  countSegmentVisit + 1;
					delete [] segmentAdjacents;
					delete [] visitSegment;
					segmentAdjacents = new Segment* [countSegmentNotVisit];
					visitSegment = new size_t [countSegmentNotVisit];
				}

				countSegmentAdjacents = 1;

				segmentAdjacents[0] = segment;
				//определяем соседей
				if (isCombineMajorSegment)
					DeterminationAdjacents(oldLayer, segment, segmentAdjacents, isNotSegmentVisit, 
					countSegmentAdjacents, isNotVisit, visitSegment, segment->maxWeight, dim);
				else
					DeterminationAdjacents(oldLayer, segment, segmentAdjacents, isNotSegmentVisit, 
					countSegmentAdjacents, isNotVisit, visitSegment, segment->maxWeight, minVoxel + 2);



				//заполнение вокселей сегмента и определение веса сегмента как максимума весов
				Voxel* oldVoxel = 0;
				oldVoxel = &newLayer->allVoxel[segment->voxel->index];
				Segment* segmentCurrent; 
				Voxel* currentVoxel = 0;
				maxWeight = segment->maxWeight;
				minWeight = segment->minWeight;

				for (size_t segmentAdjacent = 0; segmentAdjacent < countSegmentAdjacents; segmentAdjacent++)
				{
					segmentCurrent = segmentAdjacents[segmentAdjacent];
					maxWeight = max(segmentCurrent->maxWeight, maxWeight);
					minWeight = min(segmentCurrent->minWeight, minWeight);

					currentVoxel = segmentCurrent->voxel;
					oldVoxel->next = &newLayer->allVoxel[currentVoxel->index];

					while(currentVoxel->next != 0)
					{
						newLayer->allVoxel[currentVoxel->index].index = currentVoxel->index;
						newLayer->allVoxel[currentVoxel->index].segment = 0;
						newLayer->allVoxel[currentVoxel->index].next = &newLayer->allVoxel[currentVoxel->next->index];
						currentVoxel = currentVoxel->next;
						countVoxel++;
					}
					newLayer->allVoxel[currentVoxel->index].index = currentVoxel->index;
					newLayer->allVoxel[currentVoxel->index].segment = 0;
					oldVoxel = &newLayer->allVoxel[currentVoxel->index];

					isNotSegmentVisit[segmentCurrent->indexSegment] = false;
					countVoxel++;
					countSegmentVisit++;

					segmentAdjacents[segmentAdjacent] = NULL;
					if (!isCombineMajorSegment)
						if (countVoxel > minVoxel)
							break;
				}

				for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
					segmentAdjacents[segmentAdjacent] = NULL;

				sumCountVoxel += countVoxel;
				int t = 0;
				size_t newCountVoxel = 0;
				bool isStop = false;
				while ((countVoxel < minVoxel) && (!isStop))
				{
					newCountVoxel = 0;



					if ((countSegmentNotVisit / 2) > oldLayer->segmentCount -  countSegmentVisit)
					{
						countSegmentNotVisit = oldLayer->segmentCount -  countSegmentVisit + 1;
						delete [] segmentAdjacents;
						delete [] visitSegment;
						segmentAdjacents = new Segment* [countSegmentNotVisit];
						visitSegment = new size_t [countSegmentNotVisit];
					}

					countSegmentAdjacents = 1;

					segmentAdjacents[0] = segment;
					//определяем соседей

					DeterminationAdjacents(oldLayer, segment, segmentAdjacents, isNotSegmentVisit, 
						countSegmentAdjacents, isNotVisit, visitSegment, segment->maxWeight, minVoxel + 2);


					currentVoxel = 0;

					for (size_t segmentAdjacent = 1; ((segmentAdjacent < countSegmentAdjacents) && ((countVoxel + newCountVoxel) < minVoxel)); segmentAdjacent++)
					{
						segmentCurrent = segmentAdjacents[segmentAdjacent];
						maxWeight = max(segmentCurrent->maxWeight, maxWeight);
						minWeight = min(segmentCurrent->minWeight, minWeight);

						currentVoxel = segmentCurrent->voxel;
						oldVoxel->next = &newLayer->allVoxel[currentVoxel->index];

						while(currentVoxel->next != 0)
						{
							newLayer->allVoxel[currentVoxel->index].index = currentVoxel->index;
							newLayer->allVoxel[currentVoxel->index].segment = 0;
							newLayer->allVoxel[currentVoxel->index].next = &newLayer->allVoxel[currentVoxel->next->index];
							currentVoxel = currentVoxel->next;
							newCountVoxel++;
						}
						newLayer->allVoxel[currentVoxel->index].index = currentVoxel->index;
						newLayer->allVoxel[currentVoxel->index].segment = 0;
						oldVoxel = &newLayer->allVoxel[currentVoxel->index];

						isNotSegmentVisit[segmentCurrent->indexSegment] = false;
						newCountVoxel++;
						countSegmentVisit++;

						segmentAdjacents[segmentAdjacent] = NULL;
					}

					for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
						segmentAdjacents[segmentAdjacent] = NULL;
					countVoxel += newCountVoxel;
					sumCountVoxel += newCountVoxel;
					if (countSegmentAdjacents == 1)
					{
						if (step < short(floor(maxValue / 2.0)))
							step = step * 2;
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

				if (countVoxel < minVoxel)
				{

					//индексы смещения
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




					size_t adjacentsCount = 0; 
					size_t visitCount = 0;
					size_t adjacentsVoxelCount = 0;

					isNotVisit[segmentCurrent->indexSegment] = false;

					bool isStop = false;

					segmentCurrent = segment;

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
								Segment* segmentA = oldLayer->allVoxel[indexVoxel].segment;
								size_t indexiSegmentAdjacent =  segmentA->indexSegment;

								if (isNewSegment[indexiSegmentAdjacent])
								{
									if (isNotVisit[indexiSegmentAdjacent])
									{
										isNotVisit[indexiSegmentAdjacent] = false;
										visitSegment[visitCount] = indexiSegmentAdjacent;
										visitCount++;                            
										{
											segmentAdjacents[countSegmentAdjacents] = segmentA;
											countSegmentAdjacents++;
											adjacentsCount++;
											adjacentsVoxelCount += segmentA->сapacity;

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
						visitSegment[visitCount] = 0;
					}

					///*******
					Segment* minimalSegment = 0;
					size_t mins = 0;
					for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
					{
						if ((segmentAdjacents[segmentAdjacent]->сapacity < mins) && (segmentAdjacents[segmentAdjacent]->сapacity >= minVoxel))
						{
							minimalSegment = segmentAdjacents[segmentAdjacent];
							mins = segmentAdjacents[segmentAdjacent]->сapacity;
						}

					}

					Voxel* oldCurVoxel = minimalSegment->voxel;
					while (oldCurVoxel->next != 0)
					{
						oldCurVoxel = oldCurVoxel->next;
					}
					oldCurVoxel->next = &newLayer->allVoxel[segment->voxel->index];
					oldVoxel->next = NULL;
					minimalSegment->maxWeight = max(maxWeight, minimalSegment->maxWeight);
					minimalSegment->minWeight = max(minWeight, minimalSegment->minWeight);
					minimalSegment->сapacity += countVoxel;

					for (size_t segmentAdjacent = 0; (segmentAdjacent < countSegmentAdjacents); segmentAdjacent++)
						segmentAdjacents[segmentAdjacent] = NULL;

				}
				else
				{

					oldVoxel->next = NULL;
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

					Voxel* cv = &newLayer->allVoxel[segment->voxel->index];
					while(cv != 0)
					{
						cv->segment = newLayer->oldSegment;
							cv = cv->next;
					}


					newLayer->oldSegment->сapacity = countVoxel;
					newLayer->oldSegment->maxWeight = maxWeight;
					newLayer->oldSegment->minWeight = minWeight;

					if (newLayer->oldSegment->сapacity < minVoxel)
						isHaveMinorSegment = true;
					else
						isNewSegment[segment->indexSegment] = true;
				}				



			}
			segment = segment->next;
			indexSegments++;

	}
	newLayer->maxCapacity = maxCountVoxel;

	delete [] segmentAdjacents;
	delete [] isNotVisit;
	delete [] isNotSegmentVisit;
	delete [] visitSegment;

	step = oldStep;
	if (isHaveMinorSegment)
		CreateNewLayer(false);

	return newLayer;
}