#pragma once
#include "stdafx.h"
#include "GPUGraph.h"

#include <CL/opencl.h>
#include <math.h>
#include <stack>

#define max(a,b)            (((a) > (b)) ? (a) : (b))



// Host buffers for demo
// *********************************************************************

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
size_t szParmDataBytes;			// Byte size of context information
size_t szKernelLength;			// Byte size of kernel code
cl_int ciErr1, ciErr2;			// Error code var
char* cSourceCL = NULL;         // Buffer to hold source for compilation 




// Main function 
// *********************************************************************
int InitOpenCL(int iNumElements0, size_t szGlobalWorkSize0, size_t szLocalWorkSize0, 
		  int iNumElements1, size_t szGlobalWorkSize1, size_t szLocalWorkSize1, 
		  int iNumElements2, size_t szGlobalWorkSize2, size_t szLocalWorkSize2, 
		  int sx, int sy, int sz)
{

	//Get an OpenCL platform
	ciErr1 = clGetPlatformIDs(1, &cpPlatform, NULL);


	//Get the devices
	ciErr1 = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &cdDevice, NULL);



	//Create the context
	cxGPUContext = clCreateContext(0, 1, &cdDevice, NULL, NULL, &ciErr1);



	// Create a command-queue
	cqCommandQueue = clCreateCommandQueue(cxGPUContext, cdDevice, 0, &ciErr1);



	// Allocate the OpenCL buffer memory objects for source and result on the device GMEM
	cmDevSrcA = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, sizeof(short) * szGlobalWorkSize0, NULL, &ciErr1);
	cmDevSrcB = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, sizeof(size_t) * szGlobalWorkSize1, NULL, &ciErr2);
	ciErr1 |= ciErr2;
	cmDevDst = clCreateBuffer(cxGPUContext, CL_MEM_WRITE_ONLY, sizeof(short) * szGlobalWorkSize2, NULL, &ciErr2);
	ciErr1 |= ciErr2;

	//size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents

	// Read the OpenCL kernel in from source file

	cSourceCL = "__kernel void VectorAdd(__global const short* a, __global const size_t* b, __global short* c, int iNumElements, int sx, int sy, int sz)\n"\
		"{\n"\
		"// get index into global data array\n"\
		"int j = get_global_id(0);\n"\
		"// bound check (equivalent to the limit on a 'for' loop for standard/serial C code\n"\
		"if (j >= iNumElements)\n"\
		"{   \n"\
		"	return; \n"\
		"}\n"\

		"//индексы смещения\n"\
		"char relativeIndexMatrix[8][3] = {//i,j,k\n"\
		"{0,0,0},//0\n"\
		"{0,0,1},//1\n"\
		"{0,1,0},//2\n"\
		"{0,1,1},//3\n"\
		"{1,0,0},//4\n"\
		"{1,0,1},//5\n"\
		"{1,1,0},//6\n"\
		"{1,1,1},//7\n"\

		"};\n"\

		"size_t dim = sx * sy * sz;\n"\

		"//ядро\n"\

		"int indexAdjacentsVoxel = 0;\n"\

		"for (size_t k = 1; k < 8; k++)\n"\
		"{\n"\
		"indexAdjacentsVoxel = j + relativeIndexMatrix[k][0] + relativeIndexMatrix[k][1] * sx + relativeIndexMatrix[k][2] * sx * sy;\n"\
		"if ((indexAdjacentsVoxel < dim) && ((j * 7 + k - 1) < (dim * 7)))\n"\
		"c[j * 7 + k - 1] = ((indexAdjacentsVoxel >= 0) && (indexAdjacentsVoxel < dim)) ? abs(a[b[indexAdjacentsVoxel]] - a[b[j]]): 32000;\n"\

		"}\n"\

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
	ciErr1 |= clSetKernelArg(ckKernel, 3, sizeof(cl_int), (void*)&iNumElements1);
	ciErr1 |= clSetKernelArg(ckKernel, 4, sizeof(cl_int), (void*)&sx);
	ciErr1 |= clSetKernelArg(ckKernel, 5, sizeof(cl_int), (void*)&sy);
	ciErr1 |= clSetKernelArg(ckKernel, 6, sizeof(cl_int), (void*)&sz);



	// --------------------------------------------------------
	// Start Core sequence... copy input data to GPU, compute, copy results back
	return 0;
}
void KernelOpenCl(short *srcA,size_t *srcB,short *dst,
	   int iNumElements0, size_t szGlobalWorkSize0, size_t szLocalWorkSize0, 
	   int iNumElements1, size_t szGlobalWorkSize1, size_t szLocalWorkSize1, 
	   int iNumElements2, size_t szGlobalWorkSize2, size_t szLocalWorkSize2, 
	   int sx, int sy, int sz)
{
	// Asynchronous write of data to GPU device
	ciErr1 = clEnqueueWriteBuffer(cqCommandQueue, cmDevSrcA, CL_FALSE, 0, sizeof(short) * szGlobalWorkSize0, srcA, 0, NULL, NULL);
	ciErr1 |= clEnqueueWriteBuffer(cqCommandQueue, cmDevSrcB, CL_FALSE, 0, sizeof(size_t) * szGlobalWorkSize1, srcB, 0, NULL, NULL);



	// Launch kernel
	ciErr1 = clEnqueueNDRangeKernel(cqCommandQueue, ckKernel, 1, NULL, &szGlobalWorkSize1, &szLocalWorkSize1, 0, NULL, NULL);



	// Synchronous/blocking read of results, and check accumulated errors
	ciErr1 = clEnqueueReadBuffer(cqCommandQueue, cmDevDst, CL_TRUE, 0, sizeof(short) * szGlobalWorkSize2, dst, 0, NULL, NULL);
}
void ReleaseOpenCL()
{

	if(ckKernel)clReleaseKernel(ckKernel);  
	if(cpProgram)clReleaseProgram(cpProgram);
	if(cqCommandQueue)clReleaseCommandQueue(cqCommandQueue);
	if(cxGPUContext)clReleaseContext(cxGPUContext);
	if(cmDevSrcA)clReleaseMemObject(cmDevSrcA);
	if(cmDevSrcB)clReleaseMemObject(cmDevSrcB);
	if(cmDevDst)clReleaseMemObject(cmDevDst);
}




VoxelGPU::VoxelGPU()
{
	index = 0;
	next = 0;
}
VoxelGPU::~VoxelGPU()
{
	index = 0;
	next = 0;
}


//LayerSegmentsTree
LayerSegmentsTreeGPU::LayerSegmentsTreeGPU()
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
LayerSegmentsTreeGPU::~LayerSegmentsTreeGPU()
{
	maxCapacity = 0;

	down = 0;
	segmentCount = 0;
	segmentsTree = 0;

	if (indexSegments != 0)
		delete [] indexSegments;
	if (indexVoxel != 0)
			delete [] indexVoxel;
	if (startIndexVoxel != 0)
		delete [] startIndexVoxel;
	if (countVoxel != 0)
		delete [] countVoxel;
	if (maxWeight != 0)
		delete [] maxWeight;
	if (minWeight != 0)
		delete [] minWeight;
	if (up != 0)
		delete up;
}

void LayerSegmentsTreeGPU::CreateData(size_t* index, size_t count, ScanData* data)
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

	VoxelGPU* voxel = 0;
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
SegmentsTreeGPU::SegmentsTreeGPU()
{
	countLayer = 0;
	root = 0;
	step = 50;
	maxValue = 32000;
}

SegmentsTreeGPU::SegmentsTreeGPU(ScanData* data)
{
	countLayer = 0;
	root = 0;
	step = 50;
	maxValue = 32000;
	CreateRoot(data);
}
SegmentsTreeGPU::~SegmentsTreeGPU()
{
	countLayer = 0;
	root = 0;
	step = 50;
	maxValue = 32000;
	if (root != 0)
		delete root;
}

void SegmentsTreeGPU::CreateRoot(ScanData* data)
{
	scanData = data;
	root = new LayerSegmentsTreeGPU();

	size_t dim = scanData->sizeX * scanData->sizeY * scanData->sizeZ;

	root->countVoxel = new size_t [dim + 2];
	root->indexSegments = new size_t [dim + 2];
	root->indexVoxel = new VoxelGPU [dim + 2];
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

LayerSegmentsTreeGPU* SegmentsTreeGPU::GetOldLayer()
{
	LayerSegmentsTreeGPU* layer = root;
	while (layer->up != 0)
		layer = layer->up;
	return layer;
}



void SegmentsTreeGPU::Kernel(size_t sx, size_t sy, size_t sz, short* weightSegment, size_t* indexSegments, short* segmentAdjacents)
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

		size_t indexAdjacentsVoxel = 0;

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


LayerSegmentsTreeGPU* SegmentsTreeGPU::CreateNewLayer()
{
	countLayer++;

	size_t dim = scanData->sizeX * scanData->sizeY * scanData->sizeZ;

	LayerSegmentsTreeGPU* oldLayer = GetOldLayer();

	int iNumElements0 = oldLayer->segmentCount + 1;	// Length of float arrays to process (odd # for illustration)
	size_t szGlobalWorkSize0;        // 1D var for Total # of work items
	size_t szLocalWorkSize0;		    // 1D var for # of work items in the work group	
	// set and log Global and Local work size dimensions
	szLocalWorkSize0 = 256;
	szGlobalWorkSize0 = size_t(ceil(double(iNumElements0) / double (szLocalWorkSize0)) * szLocalWorkSize0);  // rounded up to the nearest multiple of the LocalWorkSize

	int iNumElements1 = dim + 2;	// Length of float arrays to process (odd # for illustration)
	size_t szGlobalWorkSize1;        // 1D var for Total # of work items
	size_t szLocalWorkSize1;		    // 1D var for # of work items in the work group	
	// set and log Global and Local work size dimensions
	szLocalWorkSize1 = 256;
	szGlobalWorkSize1 = size_t(ceil(double(iNumElements1) / double (szLocalWorkSize1)) * szLocalWorkSize1);  // rounded up to the nearest multiple of the LocalWorkSize

	int iNumElements2 = (dim + 2) * 7;	// Length of float arrays to process (odd # for illustration)
	size_t szGlobalWorkSize2;        // 1D var for Total # of work items
	size_t szLocalWorkSize2;		    // 1D var for # of work items in the work group	
	// set and log Global and Local work size dimensions
	szLocalWorkSize2 = 256;
	szGlobalWorkSize2 = size_t(ceil(double(iNumElements2) / double (szLocalWorkSize2)) * szLocalWorkSize2);  // rounded up to the nearest multiple of the LocalWorkSize



	//создание нового уровня
	LayerSegmentsTreeGPU* newLayer = new LayerSegmentsTreeGPU();
	oldLayer->up = newLayer;
	newLayer->down = oldLayer;

	newLayer->indexSegments = new size_t [szGlobalWorkSize1];
	newLayer->indexVoxel = new VoxelGPU [dim + 2];

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
	short* weightSegment = new short [szGlobalWorkSize0];
	size_t* startIndexVoxel = new size_t [oldLayer->segmentCount + 1];
	for(size_t i = 0; i < oldLayer->segmentCount; i++)
	{
		startIndexVoxel[i] = oldLayer->startIndexVoxel[i];
		countVoxel[i] = oldLayer->countVoxel[i];
		weightSegment[i] = oldLayer->maxWeight[i];
	}

	size_t tt = sizeof(short);
	size_t uuu = size_t(tt * (dim + 2) * 26 / (1024 * 1024));

	short* segmentAdjacents = new short [szGlobalWorkSize2];
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





	InitOpenCL(iNumElements0, szGlobalWorkSize0, szLocalWorkSize0, iNumElements1, szGlobalWorkSize1, szLocalWorkSize1, 
		iNumElements2, szGlobalWorkSize2, szLocalWorkSize2, scanData->sizeX, scanData->sizeY, scanData->sizeZ);



	while ((!f) && (gi < oldLayer->segmentCount))
	{
		f = true;

		//Kernel(scanData->sizeX, scanData->sizeY, scanData->sizeZ, weightSegment, newLayer->indexSegments, segmentAdjacents);
		KernelOpenCl(weightSegment, newLayer->indexSegments, segmentAdjacents, iNumElements0, szGlobalWorkSize0, szLocalWorkSize0, 
			iNumElements1, szGlobalWorkSize1, szLocalWorkSize1, 
			iNumElements2, szGlobalWorkSize2, szLocalWorkSize2, scanData->sizeX, scanData->sizeY, scanData->sizeZ);

		int indexAdjacentsVoxel = 0;
		size_t indexCurrentSegment = 0;
		size_t indexAdjacentsSegment = 0;

		VoxelGPU* currentVoxel = 0;
		VoxelGPU newVoxels;
		VoxelGPU* newVoxelsEnd = 0;
		VoxelGPU* oldVoxel = 0;
		VoxelGPU* currentAdjacentsVoxel = 0;


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
	for (size_t i = 0; i < oldLayer->segmentCount; i++)
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
	VoxelGPU* voxel = 0;
	newLayer->maxCapacity = 0;
	size_t count = 0;
	size_t c2 = 0;
	short minw = 0;
	for (size_t i = 0; i < oldLayer->segmentCount; i++)
	{
		minw = 0;
		if (isNotSegmentVisit[i])
		{
			voxel = &newLayer->indexVoxel[startIndexVoxel[i]];
			while (voxel != 0)
			{
				newLayer->indexSegments[voxel->index] = ind;

				count++;
				if (minw > scanData->data[voxel->index])
					minw = scanData->data[voxel->index];
				voxel = voxel->next;
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

	ReleaseOpenCL();
	// Free host memory



	delete [] countVoxel;
	delete [] weightSegment;
	delete [] startIndexVoxel;
	delete [] isNotSegmentVisit;
	delete [] segmentAdjacents;
	newLayer->segmentsTree = this;
	return newLayer;
}

