#include "stdafx.h"
#include "Graph.h"
#include <math.h>
#include <stack>

#define max(a,b)            (((a) > (b)) ? (a) : (b))

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
    weightSegment = 0;
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

ScanData* LayerSegmentsTree::CreateData(size_t* index, size_t count)
{
    ScanData* data = new ScanData();
    data->scaleX = segmentsTree->scanData->scaleX;
    data->scaleY = segmentsTree->scanData->scaleY;
    data->scaleZ = segmentsTree->scanData->scaleZ;
    data->sizeX = segmentsTree->scanData->sizeX;
    data->sizeY = segmentsTree->scanData->sizeY;
    data->sizeZ = segmentsTree->scanData->sizeZ;
    data->data = new short [data->sizeX * data->sizeY * data->sizeZ];
    for (size_t i = 0; i < data->sizeX * data->sizeY * data->sizeZ; i++)
        data->data[i] = 0;

    size_t j = 0;
    Segment* currentSegment = segment;
    Voxel* voxel = 0;
    while (currentSegment != 0)
    {
        if (currentSegment->indexSegment == index[j])
        {
            voxel = currentSegment->voxel;
            while (voxel != 0)
            {
                data->data[voxel->index] = segmentsTree->scanData->data[voxel->index];
                voxel = voxel->next;
            }
        }
        currentSegment = currentSegment->next;
    }    
    return data;
}

//SegmentsTree
SegmentsTree::SegmentsTree()
{
    countLayer = 0;
    root = 0;
    step = 50;
    countSegments = 0;
}

SegmentsTree::SegmentsTree(ScanData* data)
{
    countLayer = 0;
    root = 0;
    step = 50;
    countSegments = 0;
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
    segments[0].weightSegment = data->data[0];

    for (size_t i = 1; i < data->sizeX*data->sizeY*data->sizeZ; i++)
    {
        segments[i - 1].next = &segments[i];
        root->allVoxel[i].index = i;
        root->allVoxel[i].next = 0;
        root->allVoxel[i].segment = &segments[i];
        segments[i].voxel = &root->allVoxel[i];
        segments[i].indexSegment = i;
        segments[i].weightSegment = data->data[i];

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
                                          bool* isNotSegmentVisit, size_t& countSegmentAdjacents, bool* isNotVisit, size_t* visitSegment, short w)
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

    isNotVisit[segmentCurrent->indexSegment] = false;

    
    while(!stackSegments.empty())
    {
        segmentCurrent = stackSegments.top();
        stackSegments.pop();

        Voxel* currentVoxel = segmentCurrent->voxel;
        size_t indexVoxel = 0;

        std::list<Segment*>::iterator segmentAdjacent;
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
                            if (abs(w - segment->weightSegment) <= step)
                            {
                                segmentAdjacents[countSegmentAdjacents] = segment;
                                countSegmentAdjacents++;
                                adjacentsCount++;
                                stackSegments.push(segment);
                            }
                        }
                    }
                }

            }
            currentVoxel = currentVoxel->next;
        }
    }   

    for (size_t k = 0; k < visitCount; k++)
    {
        isNotVisit[visitSegment[k]] = true;
        visitSegment[visitCount] = 0;
    }
}

LayerSegmentsTree* SegmentsTree::CreateNewLayer()
{
    countSegments++;
    LayerSegmentsTree* oldLayer = GetOldLayer();

    Segment* segment = oldLayer->segment;

    bool* isNotSegmentVisit = new bool [oldLayer->segmentCount + 2];
    for (size_t i = 0; i < oldLayer->segmentCount + 2; i++)
        isNotSegmentVisit[i] = true;

    LayerSegmentsTree* newLayer = new LayerSegmentsTree();
    oldLayer->up = newLayer;
    newLayer->down = oldLayer;
    newLayer->allVoxel = new Voxel [scanData->sizeX*scanData->sizeY*scanData->sizeZ];
    newLayer->maxCapacity = 0;
    newLayer->segmentCount = 0;
    newLayer->segment = 0;
    newLayer->oldSegment = 0;
    newLayer->segmentsTree = this;


    segment = oldLayer->segment;
    indexSegments = 0;
    Segment** segmentAdjacents;

    short maxWeight = 0;
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

    while (segment != 0)
    {
        if (isNotSegmentVisit[indexSegments])
        {            
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

            DeterminationAdjacents(oldLayer, segment, segmentAdjacents, isNotSegmentVisit, 
                countSegmentAdjacents, isNotVisit, visitSegment, segment->weightSegment);

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

            //заполнение вокселей сегмента и определение веса сегмента как максимума весов
            Voxel* oldVoxel = 0;
            oldVoxel = newLayer->oldSegment->voxel;
            Segment* segmentCurrent; 
            Voxel* currentVoxel = 0;
            maxWeight = segment->weightSegment;
            for (size_t segmentAdjacent = 0; segmentAdjacent < countSegmentAdjacents; segmentAdjacent++)
            {
                segmentCurrent = segmentAdjacents[segmentAdjacent];
                maxWeight = max(segmentCurrent->weightSegment, maxWeight);

                currentVoxel = segmentCurrent->voxel;
                oldVoxel->next = &newLayer->allVoxel[currentVoxel->index];

                while(currentVoxel->next != 0)
                {
                    newLayer->allVoxel[currentVoxel->index].index = currentVoxel->index;
                    newLayer->allVoxel[currentVoxel->index].segment = newLayer->oldSegment;
                    newLayer->allVoxel[currentVoxel->index].next = &newLayer->allVoxel[currentVoxel->next->index];
                    currentVoxel = currentVoxel->next;
                    countVoxel++;
                }
                newLayer->allVoxel[currentVoxel->index].index = currentVoxel->index;
                newLayer->allVoxel[currentVoxel->index].segment = newLayer->oldSegment;
                oldVoxel = &newLayer->allVoxel[currentVoxel->index];

                isNotSegmentVisit[segmentCurrent->indexSegment] = false;
                countVoxel++;
                countSegmentVisit++;

                segmentAdjacents[segmentAdjacent] = NULL;
            }
            oldVoxel->next = NULL;
            maxCountVoxel = max(maxCountVoxel, countVoxel);
            newLayer->oldSegment->сapacity = countVoxel;
            newLayer->oldSegment->weightSegment = maxWeight;
            sumCountVoxel += countVoxel;
            

        }
        segment = segment->next;
        indexSegments++;

    }
    newLayer->maxCapacity = maxCountVoxel;
    
    delete [] segmentAdjacents;
    delete [] isNotVisit;
    delete [] isNotSegmentVisit;
    delete [] visitSegment;

    return newLayer;
}