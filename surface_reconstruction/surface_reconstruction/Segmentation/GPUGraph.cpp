#pragma once
#include "stdafx.h"
#include "GPUGraph.h"

#include <CL/opencl.h>
#include <math.h>
#include <stack>

#define max(a,b)            (((a) > (b)) ? (a) : (b))







// Name of the file with the source code for the computation kernel
// *********************************************************************
const char* cSourceFile = "VectorAdd.cl";

// Host buffers for demo
// *********************************************************************
short *srcA, *srcB, *dst;        // Host buffers for OpenCL test

// OpenCL Vars
cl_context cxGPUContext;        // OpenCL context
cl_command_queue cqCommandQueue;// OpenCL command que
cl_platform_id cpPlatform;      // OpenCL platform
cl_device_id cdDevice;          // OpenCL device
cl_program cpProgram;           // OpenCL program
cl_kernel ckKernel;             // OpenCL kernel
cl_mem cmDevSrcA;               // OpenCL device source buffer A
cl_mem cmDevSrcB;               // OpenCL device source buffer B 
cl_mem cmDevDst;                // OpenCL device destination buffer 
size_t szGlobalWorkSize;        // 1D var for Total # of work items
size_t szLocalWorkSize;		    // 1D var for # of work items in the work group	
size_t szParmDataBytes;			// Byte size of context information
size_t szKernelLength;			// Byte size of kernel code
cl_int ciErr1, ciErr2;			// Error code var
char* cSourceCL = NULL;         // Buffer to hold source for compilation 

// demo config vars
int iNumElements = 10;	// Length of float arrays to process (odd # for illustration)


// Main function 
// *********************************************************************
int main0()
{


	// set and log Global and Local work size dimensions
	szLocalWorkSize = 256;
	szGlobalWorkSize = size_t(ceil(double(iNumElements) / double (szLocalWorkSize)) * szLocalWorkSize);  // rounded up to the nearest multiple of the LocalWorkSize
	// Allocate and initialize host arrays 
	srcA = new short [szGlobalWorkSize];
	srcB = new short [szGlobalWorkSize];
	dst = new short [szGlobalWorkSize];

	for (int i = 0; i < iNumElements; i++)
	{	
		srcA[i] = i;
		srcB[i] = i + 10;
		printf("a = %d\t b = %d\n", srcA[i], srcB[i]);
	}

	//Get an OpenCL platform
	ciErr1 = clGetPlatformIDs(1, &cpPlatform, NULL);


	//Get the devices
	ciErr1 = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &cdDevice, NULL);



	//Create the context
	cxGPUContext = clCreateContext(0, 1, &cdDevice, NULL, NULL, &ciErr1);



	// Create a command-queue
	cqCommandQueue = clCreateCommandQueue(cxGPUContext, cdDevice, 0, &ciErr1);



	// Allocate the OpenCL buffer memory objects for source and result on the device GMEM
	cmDevSrcA = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, sizeof(short) * szGlobalWorkSize, NULL, &ciErr1);
	cmDevSrcB = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, sizeof(short) * szGlobalWorkSize, NULL, &ciErr2);
	ciErr1 |= ciErr2;
	cmDevDst = clCreateBuffer(cxGPUContext, CL_MEM_WRITE_ONLY, sizeof(short) * szGlobalWorkSize, NULL, &ciErr2);
	ciErr1 |= ciErr2;



	// Read the OpenCL kernel in from source file

	cSourceCL = "__kernel void VectorAdd(__global const short* a, __global const float* b, __global float* c, int iNumElements)\n"\
		"{\n"\
		"// get index into global data array\n"\
		"int iGID = get_global_id(0);\n"\
		"// bound check (equivalent to the limit on a 'for' loop for standard/serial C code\n"\
		"if (iGID >= iNumElements)\n"\
		"{   \n"\
		"	return; \n"\
		"}\n"\

		"// add the vector elements\n"\
		"c[iGID] = a[iGID] * 10;\n"\
		"}\n";

	// Create the program
	cpProgram = clCreateProgramWithSource(cxGPUContext, 1, (const char **)&cSourceCL, &szKernelLength, &ciErr1);



	// Build the program with 'mad' Optimization option
#ifdef MAC
	char* flags = "-cl-fast-relaxed-math -DMAC";
#else
	char* flags = "-cl-fast-relaxed-math";
#endif
	ciErr1 = clBuildProgram(cpProgram, 0, NULL, NULL, NULL, NULL);



	// Create the kernel
	ckKernel = clCreateKernel(cpProgram, "VectorAdd", &ciErr1);



	// Set the Argument values
	ciErr1 = clSetKernelArg(ckKernel, 0, sizeof(cl_mem), (void*)&cmDevSrcA);
	ciErr1 |= clSetKernelArg(ckKernel, 1, sizeof(cl_mem), (void*)&cmDevSrcB);
	ciErr1 |= clSetKernelArg(ckKernel, 2, sizeof(cl_mem), (void*)&cmDevDst);
	ciErr1 |= clSetKernelArg(ckKernel, 3, sizeof(cl_int), (void*)&iNumElements);



	// --------------------------------------------------------
	// Start Core sequence... copy input data to GPU, compute, copy results back
	return 0;
}
void K()
{
	// Asynchronous write of data to GPU device
	ciErr1 = clEnqueueWriteBuffer(cqCommandQueue, cmDevSrcA, CL_FALSE, 0, sizeof(short) * szGlobalWorkSize, srcA, 0, NULL, NULL);
	ciErr1 |= clEnqueueWriteBuffer(cqCommandQueue, cmDevSrcB, CL_FALSE, 0, sizeof(short) * szGlobalWorkSize, srcB, 0, NULL, NULL);



	// Launch kernel
	ciErr1 = clEnqueueNDRangeKernel(cqCommandQueue, ckKernel, 1, NULL, &szGlobalWorkSize, &szLocalWorkSize, 0, NULL, NULL);



	// Synchronous/blocking read of results, and check accumulated errors
	ciErr1 = clEnqueueReadBuffer(cqCommandQueue, cmDevDst, CL_TRUE, 0, sizeof(short) * szGlobalWorkSize, dst, 0, NULL, NULL);




	for (int i = 0; i < iNumElements; i++)
	{
		printf("c = %d\n", dst[i]);
	}
	printf("yes\n");

}
void O()
{

	if(ckKernel)clReleaseKernel(ckKernel);  
	if(cpProgram)clReleaseProgram(cpProgram);
	if(cqCommandQueue)clReleaseCommandQueue(cqCommandQueue);
	if(cxGPUContext)clReleaseContext(cxGPUContext);
	if(cmDevSrcA)clReleaseMemObject(cmDevSrcA);
	if(cmDevSrcB)clReleaseMemObject(cmDevSrcB);
	if(cmDevDst)clReleaseMemObject(cmDevDst);

	// Free host memory
	delete [] srcA; 
	delete [] srcB;
	delete []  dst;
}




Voxel2::Voxel2()
{
	index = 0;
	next = 0;
}


//LayerSegmentsTree
LayerSegmentsTree2::LayerSegmentsTree2()
{
	maxCapacity = 0;
	up = 0;
	down = 0;
	segmentCount = 0;
	segmentsTree = 0;

	indexSegments = 0;
	indexVoxel = 0;
	startIndexVoxel = 0;
	countVoxel = 0;
	maxWeight = 0;
	minWeight = 0;
}

void LayerSegmentsTree2::CreateData(size_t* index, size_t count, ScanData* data)
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

	Voxel2* voxel = 0;
	for (size_t j = 0; j < count; j++)
	{

		voxel = &indexVoxel[startIndexVoxel[index[j]]];
		while (voxel != 0)
		{
			data->data[voxel->index] = segmentsTree->scanData->data[voxel->index];
			voxel = voxel->next;
		}


	}    

}

//SegmentsTree
SegmentsTree2::SegmentsTree2()
{
	countLayer = 0;
	root = 0;
	step = 50;
	maxValue = 32000;
}

SegmentsTree2::SegmentsTree2(ScanData* data)
{
	countLayer = 0;
	root = 0;
	step = 50;
	maxValue = 32000;
	CreateRoot(data);
}

void SegmentsTree2::CreateRoot(ScanData* data)
{
	scanData = data;
	root = new LayerSegmentsTree2();

	size_t dim = scanData->sizeX * scanData->sizeY * scanData->sizeZ;

	root->countVoxel = new size_t [dim + 2];
	root->indexSegments = new size_t [dim + 2];
	root->indexVoxel = new Voxel2 [dim + 2];
	root->segmentCount = dim;
	root->startIndexVoxel  = new size_t [dim + 2];
	root->maxWeight = new short [dim + 2];
	root->minWeight = new short [dim + 2];

	for (size_t i = 0; i < dim; i++)
	{
		root->countVoxel[i] = 1;
		root->indexSegments[i] = i;
		root->indexVoxel[i].index = i;
		root->startIndexVoxel[i] = i;
		root->maxWeight[i] = scanData->data[i];	
		root->minWeight[i] = scanData->data[i];	
	}

	root->segmentsTree = this;
	root->maxCapacity = 1;
	countLayer = 1;
}

LayerSegmentsTree2* SegmentsTree2::GetOldLayer()
{
	LayerSegmentsTree2* layer = root;
	while (layer->up != 0)
		layer = layer->up;
	return layer;
}



void SegmentsTree2::Kernel(size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents)
{
	//индексы смещения
	char relativeIndexMatrix[8][3] = {//i,j,k
		{0,0,0},//0
		{0,0,1},//1
		{0,1,0},//2
		{0,1,1},//3
		{1,0,0},//4
		{1,0,1},//5
		{1,1,0},//6
		{1,1,1},//7

	};

	size_t dim = sx * sy * sz;

	for (size_t j = 0; j < dim; j++)
	{
		//ядро

		int indexAdjacentsVoxel = 0;

		for (size_t k = 1; k < 8; k++)
		{
			indexAdjacentsVoxel = j + relativeIndexMatrix[k][0] + relativeIndexMatrix[k][1] * sx +
				relativeIndexMatrix[k][2] * sx * sy;

			segmentAdjacents[j * 7 + k - 1] = ((indexAdjacentsVoxel >= 0) && (indexAdjacentsVoxel < dim)) ? 					
				abs(weightSegment[indexSegments[indexAdjacentsVoxel]] - weightSegment[indexSegments[j]]):
			maxValue;
		}
	}

}


LayerSegmentsTree2* SegmentsTree2::CreateNewLayer()
{
	countLayer++;
	main0();
	LayerSegmentsTree2* oldLayer = GetOldLayer();

	size_t dim = scanData->sizeX * scanData->sizeY * scanData->sizeZ;

	//создание нового уровня
	LayerSegmentsTree2* newLayer = new LayerSegmentsTree2();
	oldLayer->up = newLayer;
	newLayer->down = oldLayer;

	newLayer->indexSegments = new size_t [dim + 2];
	newLayer->indexVoxel = new Voxel2 [dim + 2];

	for (size_t i = 0; i < dim; i++)
	{
		newLayer->indexSegments[i] = oldLayer->indexSegments[i];
		newLayer->indexVoxel[i].index = oldLayer->indexVoxel[i].index;
		if (oldLayer->indexVoxel[i].next != 0)
			newLayer->indexVoxel[i].next = &newLayer->indexVoxel[oldLayer->indexVoxel[i].next->index];
		else
			newLayer->indexVoxel[i].next = 0;
	}

	for (size_t i = 0; i < dim; i++)
	{
		if (oldLayer->indexVoxel[i].next != 0)
			if ((newLayer->indexVoxel[i].next->index - oldLayer->indexVoxel[i].next->index) != 0)
				int ttttt = 0;
	}

	size_t* countVoxel = new size_t [oldLayer->segmentCount + 1];
	short* weightSegment = new short [oldLayer->segmentCount + 1];
	size_t* startIndexVoxel = new size_t [oldLayer->segmentCount + 1];
	for(int i = 0; i < oldLayer->segmentCount; i++)
	{
		startIndexVoxel[i] = oldLayer->startIndexVoxel[i];
		countVoxel[i] = oldLayer->countVoxel[i];
		weightSegment[i] = oldLayer->maxWeight[i];
	}

	size_t tt = sizeof(short);
	size_t uuu = size_t(tt * (dim + 2) * 26 / (1024 * 1024));

	short* segmentAdjacents = new short [(dim + 2) * 7];
	for (size_t i = 0; i < ((dim + 2) * 7); i++)
	{
		segmentAdjacents[i] = maxValue; 
	}

	bool* isNotSegmentVisit = new bool [oldLayer->segmentCount + 2];
	for (size_t i = 0; i < oldLayer->segmentCount + 2; i++)
		isNotSegmentVisit[i] = true;

	//индексы смещения
	char relativeIndexMatrix[8][3] = {//i,j,k
		{0,0,0},//0
		{0,0,1},//1
		{0,1,0},//2
		{0,1,1},//3
		{1,0,0},//4
		{1,0,1},//5
		{1,1,0},//6
		{1,1,1},//7

	};

	bool f = false;
	size_t gi = 0;


	while ((!f) && (gi < oldLayer->segmentCount))
	{
		f = true;

		Kernel(scanData->sizeX, scanData->sizeY, scanData->sizeZ, weightSegment, newLayer->indexSegments, segmentAdjacents);

		int indexAdjacentsVoxel = 0;
		size_t indexCurrentSegment = 0;
		size_t indexAdjacentsSegment = 0;

		Voxel2* currentVoxel = 0;
		Voxel2 newVoxels;
		Voxel2* newVoxelsEnd = 0;
		Voxel2* oldVoxel = 0;
		Voxel2* currentAdjacentsVoxel = 0;


		for (size_t t = 0; t < oldLayer->segmentCount; t++)
		{
			if (isNotSegmentVisit[t])
			{
				currentVoxel = &newLayer->indexVoxel[startIndexVoxel[t]];
				newVoxels.next = 0;
				newVoxelsEnd = 0;
				oldVoxel = 0;
				currentAdjacentsVoxel = 0;
				while (currentVoxel != 0)
				{
					int indexAdjacentsVoxel = 0;

					for (size_t k = 1; k < 8; k++)
					{
						indexAdjacentsVoxel = currentVoxel->index * 7 + k - 1;
						size_t siindexAdjacentsVoxel2 = currentVoxel->index + relativeIndexMatrix[k][0] + relativeIndexMatrix[k][1] * scanData->sizeX +
							relativeIndexMatrix[k][2] * scanData->sizeX * scanData->sizeY;
						if (siindexAdjacentsVoxel2 < dim)
						{
							indexAdjacentsSegment = oldLayer->indexSegments[siindexAdjacentsVoxel2];
							indexCurrentSegment = t;
							if (isNotSegmentVisit[indexAdjacentsSegment] && isNotSegmentVisit[indexCurrentSegment])
							{

								if ((segmentAdjacents[indexAdjacentsVoxel] < step) && (indexAdjacentsSegment != indexCurrentSegment))
								{

									if (newVoxels.next != 0)
									{
										newVoxelsEnd->next = &newLayer->indexVoxel[startIndexVoxel[indexAdjacentsSegment]];
									}
									else
									{
										newVoxels.next = &newLayer->indexVoxel[startIndexVoxel[indexAdjacentsSegment]];
									}
									currentAdjacentsVoxel = &newLayer->indexVoxel[startIndexVoxel[indexAdjacentsSegment]];
									isNotSegmentVisit[indexAdjacentsSegment] = false;

									while (currentAdjacentsVoxel->next != 0)
									{
										newLayer->indexSegments[currentAdjacentsVoxel->index] = indexCurrentSegment;
										currentAdjacentsVoxel = currentAdjacentsVoxel->next;
									}
									newVoxelsEnd = currentAdjacentsVoxel;
									newLayer->indexSegments[currentAdjacentsVoxel->index] = indexCurrentSegment;
									weightSegment[indexCurrentSegment] = max(weightSegment[indexCurrentSegment], weightSegment[indexAdjacentsSegment]);
									countVoxel[indexCurrentSegment] = countVoxel[indexCurrentSegment] + countVoxel[indexAdjacentsSegment];
								}
							}
						}
					}

					oldVoxel = currentVoxel;
					currentVoxel = currentVoxel->next;
				}
				if (newVoxels.next != 0)
					f = false;
				oldVoxel->next = newVoxels.next;
				size_t yyy = 0;
				currentVoxel = &newLayer->indexVoxel[startIndexVoxel[t]];
				while (currentVoxel != 0)
				{
					yyy++;
					currentVoxel = currentVoxel->next;
				}
				if (yyy != countVoxel[t])
					int ggg = 0;

			}
		}
		gi++;
	}

	newLayer->segmentCount = 0;
	for (int i = 0; i < oldLayer->segmentCount; i++)
	{
		if (isNotSegmentVisit[i])
		{
			newLayer->segmentCount++;
		}
	}

	newLayer->countVoxel = new size_t [newLayer->segmentCount + 2];
	newLayer->startIndexVoxel = new size_t [newLayer->segmentCount + 2];
	newLayer->maxWeight = new short [newLayer->segmentCount + 2];
	newLayer->minWeight = new short [newLayer->segmentCount + 2];

	size_t ind = 0;
	Voxel2* voxel = 0;
	newLayer->maxCapacity = 0;
	size_t count = 0;
	size_t c2 = 0;
	short minw = 0;
	for (int i = 0; i < oldLayer->segmentCount; i++)
	{
		minw = 0;
		if (isNotSegmentVisit[i])
		{
			voxel = &newLayer->indexVoxel[startIndexVoxel[i]];
			while (voxel != 0)
			{
				newLayer->indexSegments[voxel->index] = ind;
				voxel = voxel->next;
				count++;
				if (minw > scanData->data[voxel->index])
					minw = scanData->data[voxel->index];
			}
			newLayer->countVoxel[ind] = countVoxel[i];
			c2 += countVoxel[i];
			newLayer->startIndexVoxel[ind] = startIndexVoxel[i];
			newLayer->maxWeight[ind] = weightSegment[i];
			newLayer->minWeight[ind] = minw;
			newLayer->maxCapacity = max (newLayer->maxCapacity, newLayer->countVoxel[ind]);
			ind++;
		}
	}

	if (count != dim)
		int ggg = 0;

	O();

	delete [] countVoxel;
	delete [] weightSegment;
	delete [] startIndexVoxel;
	delete [] isNotSegmentVisit;
	delete [] segmentAdjacents;
	newLayer->segmentsTree = this;
	return newLayer;
}

