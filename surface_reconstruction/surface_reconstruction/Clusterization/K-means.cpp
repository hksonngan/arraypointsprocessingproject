#include "stdafx.h"
#include "K-means.h"
#include <math.h>
#include <cl.h>

using namespace std;

const char * source_distribution = "__kernel void distribution ( __global short	* data,			\n"\
																"__global float * means,		\n"\
																"__global unsigned int * labels,\n"\
																"unsigned int VoxelsCount,		\n"\
																"unsigned int ClustersCount )	\n"\

"{																	\n"\
 "unsigned int i = get_global_id (0);								\n"\
 "if (i<VoxelsCount)												\n"\
 "{																	\n"\
  "unsigned int optimal_cluster_id = 0;								\n"\
  "float min_dist = (float)INT_MAX;									\n"\
  "for (unsigned int j = 0; j < ClustersCount; ++j) if (means[j]>=0)\n"\
  "{																\n"\
   "float new_dist = fabs((float)data[i]-means[j]);					\n"\
   "if (new_dist < min_dist)										\n"\
   "{																\n"\
    "optimal_cluster_id = j;										\n"\
    "min_dist = new_dist;											\n"\
   "}																\n"\
  "}																\n"\
  "labels[i] = optimal_cluster_id;									\n"\
 "}																	\n"\
"}"; 

void KmeansMethod::ReleaseResources()
{
 InputData = NULL;
 Clusters = NULL;
 means = NULL;
 NClusters = 0;
 DataSize = 0;
}

KmeansMethod::KmeansMethod(ScanData *DataValue)
{
 ReleaseResources();	
 InputData = DataValue;
 DataSize = InputData->sizeX*InputData->sizeY*InputData->sizeZ;
}

KmeansMethod::KmeansMethod(Layer layer)
{
 ReleaseResources();
 InputData = new ScanData(layer);
 DataSize = layer.sizeX*layer.sizeY;
}

KmeansMethod::~KmeansMethod() { ReleaseResources(); }

void KmeansMethod::SetClustersNumber(size_t value) { NClusters = value; }

void KmeansMethod::SetCountIterations(size_t value) { CountIterations = value; }

// Вычисление центра тяжести для i-ого кластера
float KmeansMethod::GetMean(size_t i)
{
 float Sum = 0;
 vector <size_t>::iterator iter = Clusters[i].begin();
 vector <size_t>::iterator _end = Clusters[i].end();
 for (; iter!=_end; ++iter) Sum += InputData->data[*iter];
 return Sum/Clusters[i].size();
}

vector <vector <size_t> > KmeansMethod::GetClusters(BackgroundWorker^ worker)
{
 means = new float [NClusters];
 
 Clusters = new vector <size_t> [NClusters];
	
 size_t part = DataSize/NClusters;

 for (size_t i = 0; i < NClusters; ++i)
 {
  for (size_t j = part*i; j < max(DataSize*(i/(NClusters-1)), part*(i+1)); ++j)
  Clusters[i].push_back(j);
 }

 // printf("Clusters are initialized!"); _getch();

 for (size_t iter = 1; iter <= CountIterations; ++iter)
 {
  for (size_t i = 0; i < NClusters; ++i) 
  if (Clusters[i].size()>0) 
  {
   means[i] = GetMean(i); 
   Clusters[i].clear();
  }
  else means[i] = -1.0f;

  for (size_t j = 0; j < DataSize; ++j)
  {
   size_t optimal_cluster_id = 0;

   float min_dist = (float)INT_MAX;

   for (size_t k = 0; k < NClusters; ++k) if (means[k]>=0)
   {
    float new_dist = fabs((float)InputData->data[j]-means[k]);
    if (new_dist < min_dist)
    {
     optimal_cluster_id = k;
     min_dist = new_dist;
    }
   }

   Clusters[optimal_cluster_id].push_back(j);
  } 

  worker->ReportProgress(100*iter/CountIterations);
 }

 vector <vector <size_t> > result;
 result.clear();
 for (size_t i = 0; i < NClusters; ++i)
 if (Clusters[i].size()>0) result.push_back(Clusters[i]);

 return result;
}

vector <vector <size_t> > KmeansOpenCLMethod::GetClusters(BackgroundWorker^ worker)
{
  // Инициализация контекста
  cl_uint numPlatforms = 0;

  clGetPlatformIDs(0,            /* number of entries */
				   NULL,         /* платформы */
				   &numPlatforms /* число платформ */);

  cl_platform_id platform = NULL;

  if (numPlatforms > 0)
  {
   cl_platform_id * platforms = new cl_platform_id [numPlatforms];

   clGetPlatformIDs(numPlatforms, 
    	            platforms, 
				    NULL);

   platform = platforms[0];

   delete [] platforms;
  }

  // Создаём свойства контекста для заданной платформы 
  cl_context_properties properties [3] = { CL_CONTEXT_PLATFORM, (cl_context_properties) platform, 0 };

  cl_context context = clCreateContextFromType((NULL == platform) ? NULL : properties, 
											    CL_DEVICE_TYPE_GPU, 
											    NULL, 
											    NULL, 
											    NULL);

  size_t Size = 0;

  clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &Size);

  cl_device_id device = NULL;

  if (Size > 0)
  {
   cl_device_id * devices = ( cl_device_id * ) alloca ( Size );

   clGetContextInfo (context			/* context */,
                     CL_CONTEXT_DEVICES /* param_name */,
  					 Size				/* param_value_size */,
				     devices			/* param_value */,
                     NULL				/* param_value__size_ret */ );

   device = devices [0];
  }

  // Создаем очередь команд для заданного контекста и выбранного устройства
  cl_command_queue queue = clCreateCommandQueue (context /* context */,
												 device	 /* device */,
												 0		 /* properties */,
												 NULL	 /* errcode_ret */ );

 // Создаем программный объект из исходного кода (определен выше)
  size_t srclen [] = { strlen ( source_distribution ) };

  cl_program program = clCreateProgramWithSource (context						/* context */,
												  1								/* count */	 ,
												  &source_distribution			/* strings */,
												  srclen						/* lengths */,
												  NULL							/* errcode_ret */ );

  // Создаем исполняемый файл программы для выбранного устройства (GPU)
  clBuildProgram (program  /* program */,
				  1		   /* num_devices */,
				  &device  /* device_list */,
				  NULL	   /* options */,
				  NULL     /* pfn_notify */,
                  NULL     /* user_data */ );


  // Создаем объект ядра для перераспределения вокселов между кластерами
  cl_kernel kernel = clCreateKernel ( program		/* program */,
									 "distribution"	/* kernel_name */,
									  NULL			/* errcode_ret */ );

  // Создаем объект памяти в виде буфера для передачи ядру входного массива
  cl_mem input_data = clCreateBuffer (context					  /* context */,
									  CL_MEM_READ_ONLY		      /* flags */,
								      sizeof (short) * DataSize /* size */,
								      NULL					      /* host_ptr */,
								      NULL					      /* errcode_ret */ );
  
  cl_mem input_means = clCreateBuffer (context, 
									   CL_MEM_READ_ONLY, 
									   sizeof (float) * NClusters, 
									   NULL, 
									   NULL);	// буфер для передачи центров тяжести

  cl_mem output_labels = clCreateBuffer (context, 
										 CL_MEM_WRITE_ONLY, 
										 sizeof (unsigned int) * DataSize, 
										 NULL, 
										 NULL); // буфер для передачи меток кластеров
 
 // Задание аргументов ядра
  clSetKernelArg (kernel			/* kernel		*/,
				  0					/* arg_index	*/,
				  sizeof ( cl_mem )	/* arg_size		*/,
				  &input_data		/* arg_value	*/ );
 
  clSetKernelArg (kernel			/* kernel		*/,
				  1					/* arg_index	*/,
				  sizeof ( cl_mem )	/* arg_size		*/,
				  &input_means		/* arg_value	*/ );

  clSetKernelArg (kernel			/* kernel		*/,
				  2					/* arg_index	*/,
				  sizeof ( cl_mem ) /* arg_size		*/,
				  &output_labels	/* arg_value	*/ );

  clSetKernelArg (kernel, 3, sizeof (unsigned int), &DataSize);

  clSetKernelArg (kernel, 4, sizeof (unsigned int), &NClusters);

  size_t group; // максимальный размер группы работ

  // автоматическое определение максимального размера группы работ
  clGetKernelWorkGroupInfo (kernel						/* kernel */,
						    device						/* device */,
						    CL_KERNEL_WORK_GROUP_SIZE	/* param_name */,
						    sizeof ( size_t )			/* param_value_size */,
						    &group						/* param_value */,
						    NULL						/* param_value_size_ret */ );

 size_t part = DataSize/NClusters;

 means = new float [NClusters];

 Labels = new size_t [DataSize];

 Clusters = new vector <size_t> [NClusters];

 for (size_t i = 0; i < NClusters; ++i)
 {
  for (size_t j = part*i; j < max(DataSize*(i/(NClusters-1)), part*(i+1)); ++j)
  Clusters[i].push_back(j);
 }
	
 for (size_t iter = 1; iter <= CountIterations; ++iter)
 {
  // Вычисление центров тяжести кластеров
  for (size_t i = 0; i < NClusters; ++i)
  if (Clusters[i].size()>0) 
  {
   means[i] = GetMean(i); 
   Clusters[i].clear();
  }  
  else means[i] = -1.0f;

  // Помещаем в очередь команду записи входного массива в объект памяти
  clEnqueueWriteBuffer (queue						/* command_queue */,
					    input_data					/* buffer */,
					    CL_TRUE						/* blocking_write */,
					    0							/* offset */,
					    sizeof ( short ) * DataSize	/* cb */,
						InputData->data				/* ptr */,
					    0							/* num_events_in_wait_list */,
					    NULL						/* event_wait_list */,
					    NULL						/* event */ );

  clEnqueueWriteBuffer (queue, output_labels, CL_TRUE, 0, sizeof (unsigned int) * DataSize, Labels, 0, NULL, NULL);
 
  clEnqueueWriteBuffer (queue, input_means, CL_TRUE, 0, sizeof (float) * NClusters, means, 0, NULL, NULL);

  // Выполнение ядра над всем множеством входных данных
  clEnqueueNDRangeKernel (queue		/* command_queue */,
   						  kernel	/* kernel */,
						  1			/* work_dim */,
						  NULL		/* global_work_offset */,
						  &DataSize	/* global_work_size */,
						  &group	/* local_work_size */,
						  0			/* num_events_in_wait_list */,
						  NULL		/* event_wait_list */,
						  NULL		/* event */ );

  clFinish ( queue ); // Ожидаем завершения всех команд в очереди

  // Загрузка результатов вычислений с устройства
  clEnqueueReadBuffer (queue								 /* command_queue */,
					   output_labels						 /* buffer */,
					   CL_TRUE								 /* blocking_read */,
					   0									 /* offset */,
					   sizeof (unsigned int) * DataSize		 /* cb */,
					   Labels								 /* ptr */,
					   0									 /* num_events_in_wait_list */,
					   NULL									 /* event_wait_list */,
					   NULL									 /* event */ );

  // формирование новых кластеров
  for (size_t i = 0; i < DataSize; ++i) Clusters[Labels[i]].push_back(i);

  worker->ReportProgress(100*iter/CountIterations);
 }
 
 // printf("\n");

 // освобождение занятых ресурсов 
 clReleaseMemObject ( input_data );
 clReleaseMemObject ( input_means );
 clReleaseMemObject ( output_labels );
 clReleaseProgram ( program );
 clReleaseKernel ( kernel );
 clReleaseCommandQueue ( queue );
 clReleaseContext ( context );

 vector <vector <size_t> > result; result.clear();
 for (size_t i = 0; i < NClusters; ++i)
 if (Clusters[i].size()>0) result.push_back(Clusters[i]);

 return result;
}

// Класс KmeansConditionalMethod

size_t KmeansConditionalMethod::VoxelsNumberInRange()
{
 size_t result = 0;
 for (size_t i = 0; i < DataSize; ++i)
 if ((InputData->data[i]>=MinDensityRange)&&
	 (InputData->data[i]<=MaxDensityRange))
	 result++;
 return result;
}

float KmeansConditionalMethod::GetMean(size_t i)
{
 float Sum = 0;
 for (size_t i = 0; i < DataSize; ++i)
 if ((InputData->data[i]>=MinDensityRange)&&
	 (InputData->data[i]<=MaxDensityRange))
 Sum+=InputData->data[i];
 return Sum/Clusters[i].size();
}

vector <vector <size_t> > KmeansConditionalMethod::GetClusters(BackgroundWorker^ worker)
{
	// Основной код - будет написан позже
	
	vector <vector <size_t> > result; result.clear();
	for (size_t i = 0; i < NClusters; ++i) 
		if (Clusters[i].size()>0) result.push_back(Clusters[i]);
	return result;
}
